################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MiddleWares/ENTITY/motor.c 

C_DEPS += \
./MiddleWares/ENTITY/motor.d 

OBJS += \
./MiddleWares/ENTITY/motor.o 


# Each subdirectory must supply rules for building sources it contributes
MiddleWares/ENTITY/%.o MiddleWares/ENTITY/%.su MiddleWares/ENTITY/%.cyclo: ../MiddleWares/ENTITY/%.c MiddleWares/ENTITY/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MiddleWares-2f-ENTITY

clean-MiddleWares-2f-ENTITY:
	-$(RM) ./MiddleWares/ENTITY/motor.cyclo ./MiddleWares/ENTITY/motor.d ./MiddleWares/ENTITY/motor.o ./MiddleWares/ENTITY/motor.su

.PHONY: clean-MiddleWares-2f-ENTITY

