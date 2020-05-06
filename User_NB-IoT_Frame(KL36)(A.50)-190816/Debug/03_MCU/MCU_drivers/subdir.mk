################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../03_MCU/MCU_drivers/adc.c \
../03_MCU/MCU_drivers/spi.c \
../03_MCU/MCU_drivers/timer.c \
../03_MCU/MCU_drivers/tsi.c 

OBJS += \
./03_MCU/MCU_drivers/adc.o \
./03_MCU/MCU_drivers/spi.o \
./03_MCU/MCU_drivers/timer.o \
./03_MCU/MCU_drivers/tsi.o 

C_DEPS += \
./03_MCU/MCU_drivers/adc.d \
./03_MCU/MCU_drivers/spi.d \
./03_MCU/MCU_drivers/timer.d \
./03_MCU/MCU_drivers/tsi.d 


# Each subdirectory must supply rules for building sources it contributes
03_MCU/MCU_drivers/%.o: ../03_MCU/MCU_drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\02_Core" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\03_MCU" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\03_MCU\linker_file" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\03_MCU\MCU_drivers" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\03_MCU\startup" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\04_GEC" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\05_UserBoard" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\06_SoftComponent" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\07_NosPrg" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


