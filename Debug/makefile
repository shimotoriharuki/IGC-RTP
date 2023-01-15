################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
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

BUILD_ARTIFACT_NAME := Robotracer_Ryuku_Software
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Robotracer_Ryuku_Software.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Robotracer_Ryuku_Software.list \

OBJCOPY_BIN += \
Robotracer_Ryuku_Software.bin \


# All Target
all: main-build

# Main-build Target
main-build: Robotracer_Ryuku_Software.elf secondary-outputs

# Tool invocations
Robotracer_Ryuku_Software.elf: $(OBJS) $(USER_OBJS) C:\Users\ryuku\STM32CubeIDE\workspace_1.5.1\Robotracer_Ryuku_Software\STM32F405RGTX_FLASH.ld
	arm-none-eabi-gcc -o "Robotracer_Ryuku_Software.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\ryuku\STM32CubeIDE\workspace_1.5.1\Robotracer_Ryuku_Software\STM32F405RGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Robotracer_Ryuku_Software.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Robotracer_Ryuku_Software.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Robotracer_Ryuku_Software.list"
	@echo 'Finished building: $@'
	@echo ' '

Robotracer_Ryuku_Software.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Robotracer_Ryuku_Software.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY:

-include ../makefile.targets
