#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H
#include "../../MiddleWares/UTIL/parsing.h"


void UART_init(int UART_pref_num, int baudrate);
void UART_send(int UART_pref_num, int data);
int UART_Recieve(int UART_pref_num);
float UART_receive_distance(int UART_pref_num);
MOVECOMMAND UART_receive_command(int UART_pref_num);



#endif // UART_INTERFACE_H
