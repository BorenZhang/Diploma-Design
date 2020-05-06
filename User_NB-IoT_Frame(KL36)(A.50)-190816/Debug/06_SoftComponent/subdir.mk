################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../06_SoftComponent/common.c \
../06_SoftComponent/timeStamp.c \
../06_SoftComponent/valueType.c 

OBJS += \
./06_SoftComponent/common.o \
./06_SoftComponent/timeStamp.o \
./06_SoftComponent/valueType.o 

C_DEPS += \
./06_SoftComponent/common.d \
./06_SoftComponent/timeStamp.d \
./06_SoftComponent/valueType.d 


# Each subdirectory must supply rules for building sources it contributes
06_SoftComponent/%.o: ../06_SoftComponent/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\02_Core" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\03_MCU" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\03_MCU\linker_file" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\03_MCU\MCU_drivers" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\03_MCU\startup" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\04_GEC" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\05_UserBoard" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\06_SoftComponent" -I"D:\zhangqiang\DiplomaProject\experiment\UE\User_NB-IoT_Frame(KL36)(A.50)-190816\07_NosPrg" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


