################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/debug_toolbox/Src/uart_tools.c 

OBJS += \
./Core/debug_toolbox/Src/uart_tools.o 

C_DEPS += \
./Core/debug_toolbox/Src/uart_tools.d 


# Each subdirectory must supply rules for building sources it contributes
Core/debug_toolbox/Src/%.o Core/debug_toolbox/Src/%.su: ../Core/debug_toolbox/Src/%.c Core/debug_toolbox/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-debug_toolbox-2f-Src

clean-Core-2f-debug_toolbox-2f-Src:
	-$(RM) ./Core/debug_toolbox/Src/uart_tools.d ./Core/debug_toolbox/Src/uart_tools.o ./Core/debug_toolbox/Src/uart_tools.su

.PHONY: clean-Core-2f-debug_toolbox-2f-Src

