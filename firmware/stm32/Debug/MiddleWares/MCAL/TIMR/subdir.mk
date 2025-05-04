################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MiddleWares/MCAL/TIMR/TIM_program.c 

C_DEPS += \
./MiddleWares/MCAL/TIMR/TIM_program.d 

OBJS += \
./MiddleWares/MCAL/TIMR/TIM_program.o 


# Each subdirectory must supply rules for building sources it contributes
MiddleWares/MCAL/TIMR/%.o MiddleWares/MCAL/TIMR/%.su MiddleWares/MCAL/TIMR/%.cyclo: ../MiddleWares/MCAL/TIMR/%.c MiddleWares/MCAL/TIMR/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MiddleWares-2f-MCAL-2f-TIMR

clean-MiddleWares-2f-MCAL-2f-TIMR:
	-$(RM) ./MiddleWares/MCAL/TIMR/TIM_program.cyclo ./MiddleWares/MCAL/TIMR/TIM_program.d ./MiddleWares/MCAL/TIMR/TIM_program.o ./MiddleWares/MCAL/TIMR/TIM_program.su

.PHONY: clean-MiddleWares-2f-MCAL-2f-TIMR

