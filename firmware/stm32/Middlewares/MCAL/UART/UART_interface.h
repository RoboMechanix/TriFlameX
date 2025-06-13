#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include "../../Middlewares/UTIL/parsing.h"
#include "../../Core/Inc/main.h"
#include "../../UTIL/types.h"

void UART_init(int UART_pref_num, int baudrate);
void UART_send(int UART_pref_num, int data);
int UART_Receive(int UART_pref_num);  // fixed typo
UARTMessage UART_receive_message(int UART_pref_num);

extern volatile UARTMessage received_msg;
extern volatile uint8_t message_ready;

void USART1_IRQHandler(void);
void UART1_InterruptsInit(void);

extern volatile int distance ;
extern volatile int angle ;
extern volatile uint8_t command ;
extern volatile int dir ;

#endif // UART_INTERFACE_H
