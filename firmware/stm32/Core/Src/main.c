#include <main.h>

MOVECOMMAND currentCommand = CMD_NONE;
uint64_t x = 0;

void turnON(char i);
void turnOFF(char i);
char y =0;



int main(void) {

	RCC->APB2ENR |= 0xFFFFF;
	GPIOB -> CRH = 0x44442244;
	GPIOA -> CRL = 0x24444444;
	//turnON(0);

	UART_init(1,BAUDRATE);
	while (1) {
		UARTMessage msg;
		do {
		    msg = UART_receive_message(1);
		} while (msg.type == MSG_NONE);

		    switch (msg.type) {
		        case MSG_DISTANCE:
		        	if (msg.distance == 0.0f) {
		        	                turnON(0);
		        	                turnOFF(1);
		        	} else if (msg.distance == 1.0f) {
		        	                turnON(1);
		        	                turnOFF(0);
		        	}
		            break;
		        case MSG_COMMAND:
		            if (msg.command == GO) {
		            	y= 1;
		                turnON(1);
		                turnOFF(0);
		            } else if (msg.command == STOP) {
		            	turnON(0);
		            	turnOFF(1);
		            	y = 2;
		            }
		            break;
		        default:
		            // No complete message yet
		            break;
		    }

	}

}

void turnON(char i){

	switch (i){
	case 0 : GPIOB ->ODR = (1<<10); return;
	case 1 : GPIOB ->ODR = (1<<11); return;
	default : return;
	}
}

void turnOFF(char i){

	switch (i){
	case 0 : GPIOB ->ODR = ~(1<<10); return;
	case 1 : GPIOB ->ODR = ~(1<<11); return;
	default : return;
	}
}
