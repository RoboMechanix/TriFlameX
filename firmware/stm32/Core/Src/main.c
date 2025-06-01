#include "../../MiddleWares/HAL/CAR/CAR_interface.h"
#include "../../MiddleWares/HAL/CONTROL/CONTROL_interface.h"
#include "../../MiddleWares/MCAL/TIMR/TIM_interface.h"
#include "../../MiddleWares/MCAL/GPIO/GPIO_interface.h"
#include <stdint.h>
#include <stdio.h>

// === Constants ===
#define SIMULATION_DELAY_MS 70  // Delay between updates (ms)
#define PWM_FREQ_HZ 1000.0f      // PWM frequency

// === Globals ===
uint64_t current_time_ms=1 ;

// Simulated distance values (cm)
float simulated_distances[] = {
    35.0f, 35.0f, 35.0f, 35.0f, 35.0f, 35.0f, 35.5f, 35.1f, 35.0f,
	35.9f, 35.5f, 35.0f
};
int distance_count = sizeof(simulated_distances) / sizeof(simulated_distances[0]);

// Simulated angle values (degrees)
float simulated_angles[] = {
    10.0f, 8.0f, 5.0f, 2.0f, 1.0f, 0.0f, -1.0f, -2.0f, -5.0f, -8.0f, -10.0f
};
int angle_count = sizeof(simulated_angles) / sizeof(simulated_angles[0]);

// Dummy delay (for simulation only)
void delay_ms(uint32_t ms) {
    for (volatile uint32_t i = 0; i < ms * 1000; i++) {
        __asm("NOP");
    }
}

int main(void) {
    // === Left Motor (TIM3, PA4/PA5) ===


	TIM_TypeDef *leftTimer = TIM3;
    uint8_t leftChannel = 1;
    GPIO_TypeDef *leftDir1Port = GPIOA; uint8_t leftDir1Pin = 4;
    GPIO_TypeDef *leftDir2Port = GPIOA; uint8_t leftDir2Pin = 5;

    // === Right Motor (TIM4, PB6/PB7) ===
    TIM_TypeDef *rightTimer = TIM4;
    uint8_t rightChannel = 1;
    GPIO_TypeDef *rightDir1Port = GPIOA; uint8_t rightDir1Pin = 2;
    GPIO_TypeDef *rightDir2Port = GPIOA; uint8_t rightDir2Pin = 3;

    // === Init Car Motors ===
    CAR_init(leftTimer, leftChannel, PWM_FREQ_HZ,
             leftDir1Port, leftDir2Port, leftDir1Pin, leftDir2Pin,
             rightTimer, rightChannel, PWM_FREQ_HZ,
             rightDir1Port, rightDir2Port, rightDir1Pin, rightDir2Pin);

    // === Init Millisecond Timer (TIM2 used for timing) ===
    TIM_initMillis(TIM2, 1);  // 1ms resolution
    delay_ms(500);

    // === Initialize PD controllers ===
    PD_init(6.0f, 3.0f);        // Distance PD
    PD_init_angle(8.0f, 1.0f);  // Angle control gains

    for (int i = 0; i < distance_count; i++) {
        float distance = simulated_distances[i];
        float angle = simulated_angles[i % angle_count]; // Loop angles if fewer

        current_time_ms = TIM_Millis();
        // Update distance control (forward/backward speed)
        PD_update_from_distance(distance, current_time_ms);

        // Update angle control (turning)

        PD_update_angle(angle, current_time_ms);


        delay_ms(SIMULATION_DELAY_MS);
    }

    CAR_stop();  // Stop motors at end of simulation

    while (1);
}
