################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD_Driver/Src/lcd_driver.c 

OBJS += \
./LCD_Driver/Src/lcd_driver.o 

C_DEPS += \
./LCD_Driver/Src/lcd_driver.d 


# Each subdirectory must supply rules for building sources it contributes
LCD_Driver/Src/%.o: ../LCD_Driver/Src/%.c LCD_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/franz/OneDrive/Desktop/BME/Semester 3/Programming of Microcontrollers/uctrl_project/franziska/Potentiometer/Inc" -I"C:/Users/franz/OneDrive/Desktop/BME/Semester 3/Programming of Microcontrollers/uctrl_project/franziska/LCD_Driver/Inc" -I"C:/Users/franz/OneDrive/Desktop/BME/Semester 3/Programming of Microcontrollers/uctrl_project/franziska/Scale/Inc" -I"C:/Users/franz/OneDrive/Desktop/BME/Semester 3/Programming of Microcontrollers/uctrl_project/franziska/HX711/Inc" -I"C:/Users/franz/OneDrive/Desktop/BME/Semester 3/Programming of Microcontrollers/uctrl_project/franziska/Communication/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

