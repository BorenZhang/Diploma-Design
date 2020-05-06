################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include 07_NosPrg/subdir.mk
-include 06_SoftComponent/subdir.mk
-include 05_UserBoard/subdir.mk
-include 04_GEC/subdir.mk
-include 03_MCU/startup/subdir.mk
-include 03_MCU/MCU_drivers/subdir.mk
-include subdir.mk
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
SECONDARY_FLASH += \
User_NB-IoT-Frame(KL36)A.50.hex \

SECONDARY_LIST += \
User_NB-IoT-Frame(KL36)A.50.lst \


# All Target
all: User_NB-IoT-Frame(KL36)A.50.elf secondary-outputs

# Tool invocations
User_NB-IoT-Frame(KL36)A.50.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\03_MCU\linker_file\MKL36Z64xxx4_flash.ld" -Xlinker --gc-sections -Wl,-Map,"User_NB-IoT-Frame(KL36)A.50.map" -specs=nano.specs -specs=nosys.specs -o "User_NB-IoT-Frame(KL36)A.50.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

User_NB-IoT-Frame(KL36)A.50.hex: User_NB-IoT-Frame(KL36)A.50.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "User_NB-IoT-Frame(KL36)A.50.elf"  "User_NB-IoT-Frame(KL36)A.50.hex"
	@echo 'Finished building: $@'
	@echo ' '

User_NB-IoT-Frame(KL36)A.50.lst: User_NB-IoT-Frame(KL36)A.50.elf
	@echo 'Invoking: Cross ARM GNU Create Listing'
	arm-none-eabi-objdump --source --all-headers --demangle --line-numbers --wide "User_NB-IoT-Frame(KL36)A.50.elf" > "User_NB-IoT-Frame(KL36)A.50.lst"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(CC_DEPS)$(SECONDARY_FLASH)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS)$(SECONDARY_LIST)$(S_UPPER_DEPS) User_NB-IoT-Frame(KL36)A.50.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
