################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../03_MCU/startup/system_MKL36Z4.c 

S_UPPER_SRCS += \
../03_MCU/startup/startup_MKL36Z4.S 

OBJS += \
./03_MCU/startup/startup_MKL36Z4.o \
./03_MCU/startup/system_MKL36Z4.o 

C_DEPS += \
./03_MCU/startup/system_MKL36Z4.d 

S_UPPER_DEPS += \
./03_MCU/startup/startup_MKL36Z4.d 


# Each subdirectory must supply rules for building sources it contributes
03_MCU/startup/%.o: ../03_MCU/startup/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

03_MCU/startup/%.o: ../03_MCU/startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\02_Core" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\03_MCU" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\03_MCU\linker_file" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\03_MCU\MCU_drivers" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\03_MCU\startup" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\04_GEC" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\05_UserBoard" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\06_SoftComponent" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\07_NosPrg" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


