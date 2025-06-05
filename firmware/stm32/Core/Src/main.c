/* Includes ------------------------------------------------------------------*/
#include "main.h"
// === Globals ===
uint64_t current_time_ms = 1;


// === Variables ===

uint16_t angle = 0.0f;
float realangle = 0.0f;

void turnON(char i);
void turnOFF(char i);
char y =0;
uint16_t distance;

int main(void) {

				RCC->APB2ENR |= 0xFFFFF;
				GPIOB -> CRH = 0x44442244;
				GPIOA -> CRL = 0x24444444;

	while (1){
			//turnON(0);
			UART_init(1,BAUDRATE);
			while (1) {
				UARTMessage msg;
				do {
				    msg = UART_receive_message(1);
				} while (msg.type == MSG_NONE);
				    switch (msg.type) {
				        case MSG_COMMAND_DISTANCE_ANGLE:
				        if (msg.command == 1) {
				                       // GO
				         //turnON(1);
				         //turnOFF(0);
				        } else {
				        	                // STOP
				        //turnON(0);
				        //turnOFF(1);

				        }

				        distance = msg.distance;
				        if (distance < 70 && distance >= 0){
				        	turnON(1);
				        	turnOFF(0);
				        }
				        else {
				        	turnON(0);
				        	turnOFF(1);
				        }
				        angle = msg.angle;
				            break;
				        default:
				            break;

				    }
			}
	}
}

void turnON(char i){
	switch (i){
		case 0 : GPIOB ->ODR |= (1<<10); return;
		case 1 : GPIOB ->ODR |= (1<<11); return;
		default : return;
		}
}

void turnOFF(char i){
	switch (i){
		case 0 : GPIOB ->ODR &= ~(1<<10); return;
		case 1 : GPIOB ->ODR &= ~(1<<11); return;
		default : return;
		}
}


