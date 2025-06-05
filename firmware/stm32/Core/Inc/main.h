#ifndef MAIN_H
#define MAIN_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f103xb.h"

// === FreeRTOS ===
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"
#include "event_groups.h"

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h> // for atof()

#include "../../Middlewares/UTIL/parsing.h"
#include "../../Middlewares/HAL/CAR/CAR_interface.h"
#include "../../Middlewares/MCAL/TIMR/TIM_interface.h"
#include "../../Middlewares/MCAL/GPIO/GPIO_interface.h"
#include "../../Middlewares/MCAL/UART/UART_interface.h"
#include "../../Middlewares/HAL/CONTROL/CONTROL_interface.h"


// === Constants ===
#define SIMULATION_DELAY_MS 70  // Delay between updates (ms)
#define PWM_FREQ_HZ 1000.0f      // PWM frequency
#define UART_BUFFER_SIZE 64
#define BAUDRATE 115200








extern MOVECOMMAND currentCommand;

#endif
