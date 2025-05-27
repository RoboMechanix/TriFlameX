#include <main.h>

MOVECOMMAND currentCommand = CMD_NONE;
uint64_t x = 0;
int main(void) {

	TIM_initMillis(TIM2, 1);
	TIM2->CNT=59000;
	while (1) {

		x = TIM_Millis();

//TIM_delay(TIM3, 2000);

	}

}
