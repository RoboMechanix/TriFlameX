#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H
void UART_init(int UART_pref_num, int baudrate);
void UART_send(int UART_pref_num, int data);
int UART_Recieve(int UART_pref_num);


#endif // UART_INTERFACE_H
