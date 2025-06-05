################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/HAL/CAR/CAR_program.c 

C_DEPS += \
./Middlewares/HAL/CAR/CAR_program.d 

OBJS += \
./Middlewares/HAL/CAR/CAR_program.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/HAL/CAR/%.o Middlewares/HAL/CAR/%.su Middlewares/HAL/CAR/%.cyclo: ../Middlewares/HAL/CAR/%.c Middlewares/HAL/CAR/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-HAL-2f-CAR

clean-Middlewares-2f-HAL-2f-CAR:
	-$(RM) ./Middlewares/HAL/CAR/CAR_program.cyclo ./Middlewares/HAL/CAR/CAR_program.d ./Middlewares/HAL/CAR/CAR_program.o ./Middlewares/HAL/CAR/CAR_program.su

.PHONY: clean-Middlewares-2f-HAL-2f-CAR

