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

UARTMessage UART_receive_message(int UART_pref_num) {
    static enum { WAIT_START, READ_DATA, READ_CHECKSUM, WAIT_END } state = WAIT_START;
    static uint8_t buffer[3];
    static uint8_t index = 0;
    static uint8_t checksum = 0;

    USART_TypeDef *USARTx;
    switch (UART_pref_num) {
        case 1: USARTx = USART1; break;
        case 2: USARTx = USART2; break;
        case 3: USARTx = USART3; break;
        default: return (UARTMessage){ .type = MSG_NONE };
    }

    if (!(USARTx->SR & USART_SR_RXNE)) return (UARTMessage){ .type = MSG_NONE };
    uint8_t byte = USARTx->DR & 0xFF;

    switch (state) {
        case WAIT_START:
            if (byte == 0xAA) {
                index = 0;
                checksum = 0;
                state = READ_DATA;
            }
            break;

        case READ_DATA:
            buffer[index++] = byte;
            checksum ^= byte;
            if (index == 3) state = READ_CHECKSUM;
            break;

        case READ_CHECKSUM:
            if (byte == checksum) {
                state = WAIT_END;
            } else {
                state = WAIT_START;
            }
            break;

        case WAIT_END:
            if (byte == 0x55) {
                // ACK
                while (!(USARTx->SR & USART_SR_TXE));
                USARTx->DR = 0xCC;

                uint32_t packed = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];
                int command = (packed >> 23) & 0x01;
                int dir     = (packed >> 22) & 0x01;
                int distance = (packed >> 8) & 0x3FFF;
                int sign = (packed >> 7) & 0x01;
                int angle = packed & 0x7F;
                if (sign) angle = -angle;

                UARTMessage msg = {
                    .type = MSG_COMMAND_DISTANCE_ANGLE,
                    .command = command,
                    .dir = dir,
                    .distance = distance,
                    .angle = angle
                };
                state = WAIT_START;
                return msg;
            } else {
                state = WAIT_START;
            }
            break;
    }

    return (UARTMessage){ .type = MSG_NONE };
}

