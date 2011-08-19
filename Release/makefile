################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include xbee-arduino-read-only/subdir.mk
-include XbeeLib/xbeeSendRseries2/subdir.mk
-include XbeeLib/xbeeSendRseries1/subdir.mk
-include XbeeLib/xbeeLibrary/subdir.mk
-include XbeeLib/xbeeIOdataparser/subdir.mk
-include XbeeLib/xbeeATseries2/subdir.mk
-include XbeeLib/xbeeATseries1/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Test2.lss \

FLASH_IMAGE += \
Test2.hex \

EEPROM_IMAGE += \
Test2.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Test2.elf secondary-outputs

# Tool invocations
Test2.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-g++ -Wl,-Map,Test2.map,--cref -L/Users/XtremD/Documents/workspace/Test2 -mmcu=atmega1280 -o "Test2.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Test2.lss: Test2.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Test2.elf  >"Test2.lss"
	@echo 'Finished building: $@'
	@echo ' '

Test2.hex: Test2.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex Test2.elf  "Test2.hex"
	@echo 'Finished building: $@'
	@echo ' '

Test2.eep: Test2.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Test2.elf  "Test2.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Test2.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega1280 Test2.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EEPROM_IMAGE)$(ELFS)$(FLASH_IMAGE)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) Test2.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
