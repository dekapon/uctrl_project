################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD_Menu/Src/lcd_menu.c 

OBJS += \
./LCD_Menu/Src/lcd_menu.o 

C_DEPS += \
./LCD_Menu/Src/lcd_menu.d 


# Each subdirectory must supply rules for building sources it contributes
LCD_Menu/Src/%.o: ../LCD_Menu/Src/%.c LCD_Menu/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/franz/OneDrive/Desktop/BME/Semester 3/Programming of Microcontrollers/uctrl_project/franziska/Potentiometer/Inc" -I"C:/Users/franz/OneDrive/Desktop/BME/Semester 3/Programming of Microcontrollers/uctrl_project/franziska/LCD_Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

