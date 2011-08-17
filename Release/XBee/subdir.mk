################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../XBee/XBee.cpp 

OBJS += \
./XBee/XBee.o 

CPP_DEPS += \
./XBee/XBee.d 


# Each subdirectory must supply rules for building sources it contributes
XBee/%.o: ../XBee/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/Users/XtremD/Documents/workspace/Test2/XBee" -I"/Users/XtremD/Documents/workspace/Test2/aes" -I"/Users/XtremD/Documents/workspace/Test2/Arduino Cores" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -Wl,--gc-sections --param inline-call-cost=2 -finline-limit=3 -fno-inline-small-functions -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega1280 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


