################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../main.cpp 

OBJS += \
./main.o 

CPP_DEPS += \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/Users/XtremD/Documents/workspace/Test2/XbeeLib -I"/Users/XtremD/Documents/workspace/Test2/aes" -I"/Users/XtremD/Documents/workspace/Test2/Arduino Cores" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -Wl,--gc-sections --param inline-call-cost=2 -finline-limit=3 -fno-inline-small-functions -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega1280 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


