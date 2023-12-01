################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/debug_toolbox/Src/uart_tools.c 

OBJS += \
./Core/debug_toolbox/Src/uart_tools.o 

C_DEPS += \
./Core/debug_toolbox/Src/uart_tools.d 


# Each subdirectory must supply rules for building sources it contributes
Core/debug_toolbox/Src/%.o Core/debug_toolbox/Src/%.su Core/debug_toolbox/Src/%.cyclo: ../Core/debug_toolbox/Src/%.c Core/debug_toolbox/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-debug_toolbox-2f-Src

clean-Core-2f-debug_toolbox-2f-Src:
	-$(RM) ./Core/debug_toolbox/Src/uart_tools.cyclo ./Core/debug_toolbox/Src/uart_tools.d ./Core/debug_toolbox/Src/uart_tools.o ./Core/debug_toolbox/Src/uart_tools.su

.PHONY: clean-Core-2f-debug_toolbox-2f-Src

