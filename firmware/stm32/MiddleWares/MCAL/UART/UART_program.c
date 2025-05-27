#include "UART_interface.h"
#include "stm32f103xb.h"
#include "../../UTIL/BIT_MATH.h"
#include "../GPIO/GPIO_interface.h"

#define RX_BUFFER_LEN 64

void UART_init(int UART_pref_num, int baudrate)
{
    USART_TypeDef *USARTx;
    uint32_t pclk = 8000000; // 8 MHz clock
    //uint32_t brr_value; //unused var

    switch (UART_pref_num)
    {
    case 1:
        SET_BIT(RCC->APB2ENR, 14);            // USART1
        SET_BIT(RCC->APB2ENR, 2);             // GPIOA
        GPIO_pinMode(GPIOA, 9, AF_PP);        // TX
        GPIO_pinMode(GPIOA, 10, INPUT_FLOAT); // RX
        USARTx = USART1;
        break;

    case 2:
        SET_BIT(RCC->APB1ENR, 17);           // USART2
        SET_BIT(RCC->APB2ENR, 2);            // GPIOA
        GPIO_pinMode(GPIOA, 2, AF_PP);       // TX
        GPIO_pinMode(GPIOA, 3, INPUT_FLOAT); // RX
        USARTx = USART2;
        break;

    case 3:
        SET_BIT(RCC->APB1ENR, 18);            // USART3
        SET_BIT(RCC->APB2ENR, 3);             // GPIOB
        GPIO_pinMode(GPIOB, 10, AF_PP);       // TX
        GPIO_pinMode(GPIOB, 11, INPUT_FLOAT); // RX
        USARTx = USART3;
        break;

    default:
        return;
    }

    // Baud Rate Calculation for 8 MHz clock
    float usartdiv = (float)pclk / (16.0f * baudrate);
    uint16_t mantissa = (uint16_t)usartdiv;
    uint16_t fraction = (uint16_t)((usartdiv - mantissa) * 16.0f + 0.5f); // rounded

    USARTx->BRR = (mantissa << 4) | (fraction & 0xF);

    // Enable USART, TX, RX
    SET_BIT(USARTx->CR1, 13); // UE
    SET_BIT(USARTx->CR1, 3);  // TE
    SET_BIT(USARTx->CR1, 2);  // RE
}

void UART_send(int UART_pref_num, int data)
{
    USART_TypeDef *USARTx;

    switch (UART_pref_num)
    {
    case 1: USARTx = USART1; break;
    case 2: USARTx = USART2; break;
    case 3: USARTx = USART3; break;
    }

    while (!(USARTx->SR & (1 << 7)));
    USARTx->DR = (data & 0xFF);
}

int UART_Receive(int UART_pref_num)
{
    USART_TypeDef *USARTx;

    switch (UART_pref_num)
    {
    case 1: USARTx = USART1; break;
    case 2: USARTx = USART2; break;
    case 3: USARTx = USART3; break;
    }

    while (!(USARTx->SR & (1 << 5)));

    return USARTx->DR & 0xFF;
}

float UART_receive_distance(int UART_pref_num)
{
    static char rx_buffer[RX_BUFFER_LEN];
    static uint8_t rx_index = 0;

    USART_TypeDef *USARTx;

    switch (UART_pref_num)
    {
    case 1: USARTx = USART1; break;
    case 2: USARTx = USART2; break;
    case 3: USARTx = USART3; break;
    default: return -1.0f;
    }

    // Wait for a new character
    if (!(USARTx->SR & (1 << 5))) return -1.0f; // No data yet

    char c = USARTx->DR & 0xFF;

    if (c == '\n')
    {
        rx_buffer[rx_index] = '\0'; // Null-terminate the string
        rx_index = 0;
        return parse_distance_message(rx_buffer); // Use external parser
    }
    else if (rx_index < RX_BUFFER_LEN - 1)
    {
        rx_buffer[rx_index++] = c;
    }
    else
    {
        rx_index = 0; // Reset on overflow
    }

    return -1.0f; // No complete message yet
}

MOVECOMMAND UART_receive_command(int UART_pref_num)
{
    static char rx_buffer[32];
    static uint8_t rx_index = 0;

    USART_TypeDef *USARTx;

    switch (UART_pref_num)
    {
    case 1: USARTx = USART1; break;
    case 2: USARTx = USART2; break;
    case 3: USARTx = USART3; break;
    default: return CMD_NONE;
    }

    // Wait for character
    if (!(USARTx->SR & (1 << 5))) return CMD_NONE;

    char c = USARTx->DR & 0xFF;

    if (c == '\n')
    {
        rx_buffer[rx_index] = '\0';
        rx_index = 0;
        return parse_command_message(rx_buffer);
    }
    else if (rx_index < sizeof(rx_buffer) - 1)
    {
        rx_buffer[rx_index++] = c;
    }
    else
    {
        rx_index = 0; // Reset if overflow
    }

    return CMD_NONE;
}




