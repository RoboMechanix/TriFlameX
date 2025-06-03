################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/MCAL/TIMR/TIM_program.c 

C_DEPS += \
./Middlewares/MCAL/TIMR/TIM_program.d 

OBJS += \
./Middlewares/MCAL/TIMR/TIM_program.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/MCAL/TIMR/%.o Middlewares/MCAL/TIMR/%.su Middlewares/MCAL/TIMR/%.cyclo: ../Middlewares/MCAL/TIMR/%.c Middlewares/MCAL/TIMR/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-MCAL-2f-TIMR

clean-Middlewares-2f-MCAL-2f-TIMR:
	-$(RM) ./Middlewares/MCAL/TIMR/TIM_program.cyclo ./Middlewares/MCAL/TIMR/TIM_program.d ./Middlewares/MCAL/TIMR/TIM_program.o ./Middlewares/MCAL/TIMR/TIM_program.su

.PHONY: clean-Middlewares-2f-MCAL-2f-TIMR

