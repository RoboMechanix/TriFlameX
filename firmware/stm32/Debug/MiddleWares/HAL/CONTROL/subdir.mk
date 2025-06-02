################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MiddleWares/HAL/CONTROL/CONTROL_program.c 

C_DEPS += \
./MiddleWares/HAL/CONTROL/CONTROL_program.d 

OBJS += \
./MiddleWares/HAL/CONTROL/CONTROL_program.o 


# Each subdirectory must supply rules for building sources it contributes
MiddleWares/HAL/CONTROL/%.o MiddleWares/HAL/CONTROL/%.su MiddleWares/HAL/CONTROL/%.cyclo: ../MiddleWares/HAL/CONTROL/%.c MiddleWares/HAL/CONTROL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -IMiddlewares/Third_Party/FreeRTOS/Source/include -IMiddlewares/Third_Party/FreeRTOS/Source/portable/[Compiler]/[Architecture] -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MiddleWares-2f-HAL-2f-CONTROL

clean-MiddleWares-2f-HAL-2f-CONTROL:
	-$(RM) ./MiddleWares/HAL/CONTROL/CONTROL_program.cyclo ./MiddleWares/HAL/CONTROL/CONTROL_program.d ./MiddleWares/HAL/CONTROL/CONTROL_program.o ./MiddleWares/HAL/CONTROL/CONTROL_program.su

.PHONY: clean-MiddleWares-2f-HAL-2f-CONTROL

