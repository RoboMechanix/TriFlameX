#include "../../MiddleWares/HAL/CAR/CAR_interface.h"
#include "../../MiddleWares/MCAL/TIMR/TIM_interface.h"
#include "../../MiddleWares/MCAL/GPIO/GPIO_interface.h"
#include <stdint.h>

// Dummy delay function (replace with HAL_Delay or TIM delay if available)
void delay_ms(uint32_t ms) {
    for (volatile uint32_t i = 0; i < ms * 1000; i++) {
        __asm("NOP");
    }
}

int main(void) {
    // Example hardware configuration (adjust if needed)
    TIM_TypeDef *leftTimer = TIM3;    // PA6 (CH1)
    TIM_TypeDef *rightTimer = TIM2;   // PA0 (CH1)

    uint8_t leftChannel = 1;          // TIM3_CH1
    uint8_t rightChannel = 1;         // TIM2_CH1

    GPIO_TypeDef *dirPin1 = GPIOA;    // Direction pin for Right Motor
    uint8_t dirPin1Num = 2;           // PA2 (no conflict with PWM)

    GPIO_TypeDef *dirPin2 = GPIOA;    // Direction pin for Left Motor
    uint8_t dirPin2Num = 3;           // PA3 (no conflict with PWM)

    // Initialize the car system
    CAR_init(leftTimer, leftChannel, 1000.0f, dirPin1, dirPin1Num,
             rightTimer, rightChannel, 1000.0f, dirPin2, dirPin2Num);

    // Test forward movement
    CAR_forward(90.0f);  // 70% speed
    delay_ms(2000);

    // Test backward movement
    CAR_backwards(90.0f);
    delay_ms(2000);

    // Test right turn
    CAR_right(90.0f);
    delay_ms(2000);

    // Test left turn
    CAR_left(90.0f);
    delay_ms(2000);

    // Test stop
    CAR_stop();
//STM32F103 Pin	Function	L298N Pin
//    PA6	PWM Left Motor	ENA
//    PA0	PWM Right Motor	ENB
//    PA2	Dir for Right	IN1
//    PA3	Dir for Left	IN2
    while (1) {
        // Infinite loop
    }

    return 0;
}
