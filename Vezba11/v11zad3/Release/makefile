################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
v11zad3.lss \

FLASH_IMAGE += \
v11zad3.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: v11zad3.elf secondary-outputs

# Tool invocations
v11zad3.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,v11zad3.map -L"C:\Users\LJ\eclipse-workspace\PLS7\Release" -mmcu=atmega328p -o "v11zad3.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

v11zad3.lss: v11zad3.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S v11zad3.elf  >"v11zad3.lss"
	@echo 'Finished building: $@'
	@echo ' '

v11zad3.hex: v11zad3.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex v11zad3.elf  "v11zad3.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: v11zad3.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p v11zad3.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: v11zad3.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm328p -carduino -PCOM3 -Uflash:w:v11zad3.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) v11zad3.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
