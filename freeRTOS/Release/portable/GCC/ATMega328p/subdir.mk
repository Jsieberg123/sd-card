################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../portable/GCC/ATMega328p/port.c 

C_DEPS += \
./portable/GCC/ATMega328p/port.d 

OBJS += \
./portable/GCC/ATMega328p/port.o 


# Each subdirectory must supply rules for building sources it contributes
portable/GCC/ATMega328p/%.o: ../portable/GCC/ATMega328p/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/jacob/workspace/freeRTOS/include" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


