#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H
#include "../../MiddleWares/UTIL/parsing.h"
#include "../../Core/Inc/main.h"
#include "../../UTIL/types.h"

void UART_init(int UART_pref_num, int baudrate);
void UART_send(int UART_pref_num, int data);
int UART_Recieve(int UART_pref_num);


UARTMessage UART_receive_message(int UART_pref_num);

/*
 * UARTMessage UART_receive_message(int UART_pref_num)
 *
 * This function reads characters from the selected UART port and builds a message
 * terminated by a newline `\n`. It distinguishes between:
 *
 *   - Distance messages: raw float values (e.g., "123.45\n")
 *   - Command messages: string commands like "GO\n" or "STOP\n"
 *
 * Parameters:
 *   UART_pref_num — UART port number: 1 (USART1), 2 (USART2), 3 (USART3)
 *
 * Returns:
 *   UARTMessage struct containing:
 *     - type: MSG_NONE, MSG_DISTANCE, or MSG_COMMAND
 *     - distance: if type == MSG_DISTANCE
 *     - command: if type == MSG_COMMAND
 *
 * Usage Example:
 *
 *   UARTMessage msg = UART_receive_message(1);
 *
 *   switch (msg.type) {
 *       case MSG_DISTANCE:
 *           // Use msg.distance (float value)
 *           break;
 *       case MSG_COMMAND:
 *           if (msg.command == CMD_GO) {
 *               // Start motors
 *           } else if (msg.command == CMD_STOP) {
 *               // Stop motors
 *           }
 *           break;
 *       default:
 *           // No complete message yet
 *           break;
 *   }
 */

#endif // UART_INTERFACE_H
