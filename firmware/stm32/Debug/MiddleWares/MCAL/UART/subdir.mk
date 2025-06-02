################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MiddleWares/MCAL/UART/UART_program.c 

C_DEPS += \
./MiddleWares/MCAL/UART/UART_program.d 

OBJS += \
./MiddleWares/MCAL/UART/UART_program.o 


# Each subdirectory must supply rules for building sources it contributes
MiddleWares/MCAL/UART/%.o MiddleWares/MCAL/UART/%.su MiddleWares/MCAL/UART/%.cyclo: ../MiddleWares/MCAL/UART/%.c MiddleWares/MCAL/UART/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -IMiddlewares/Third_Party/FreeRTOS/Source/include -IMiddlewares/Third_Party/FreeRTOS/Source/portable/[Compiler]/[Architecture] -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MiddleWares-2f-MCAL-2f-UART

clean-MiddleWares-2f-MCAL-2f-UART:
	-$(RM) ./MiddleWares/MCAL/UART/UART_program.cyclo ./MiddleWares/MCAL/UART/UART_program.d ./MiddleWares/MCAL/UART/UART_program.o ./MiddleWares/MCAL/UART/UART_program.su

.PHONY: clean-MiddleWares-2f-MCAL-2f-UART

