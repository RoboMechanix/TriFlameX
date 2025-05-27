#ifndef MAIN_H
#define MAIN_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f103xb.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../MiddleWares/HAL/CAR/CAR_interface.h"
#include "../../MiddleWares/MCAL/TIMR/TIM_interface.h"
#include "../../MiddleWares/MCAL/GPIO/GPIO_interface.h"
#include "../../MiddleWares/MCAL/UART/UART_interface.h"
#include <stdint.h>
//#include "../../MiddleWares/UTIL/parsing.h"


#define BAUDRATE 115200




extern MOVECOMMAND currentCommand;

#endif
