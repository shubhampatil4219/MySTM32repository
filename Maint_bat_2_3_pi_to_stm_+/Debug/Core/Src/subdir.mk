################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Bat1_Maint_SPCI_RTE.c \
../Core/Src/Bat1_Update_Info_during_Maintenance.c \
../Core/Src/Bat2_Update_Info_during_Maintenance.c \
../Core/Src/Bat3_Update_Info_during_Maintenance.c \
../Core/Src/Battery1_Maintenance_General_Info.c \
../Core/Src/Battery1_Maintenance_Specific_Info.c \
../Core/Src/Battery2_Maintenance_General_Info.c \
../Core/Src/Battery3_Maintenance_General_Info.c \
../Core/Src/Commands_from_Raspi_To_STM32.c \
../Core/Src/Handle_Gpio_pins.c \
../Core/Src/Results_Auto_Test_Bat1_Maintenance.c \
../Core/Src/Results_Auto_Test_Bat2_Maintenance.c \
../Core/Src/Results_Auto_Test_Bat3_Maintenance.c \
../Core/Src/Specific_parameters_main_BAT1.c \
../Core/Src/Specific_parameters_main_BAT2.c \
../Core/Src/Specific_parameters_main_BAT3.c \
../Core/Src/SubStatemachine_bat1_Maintenance.c \
../Core/Src/SubStatemachine_bat2_Maintenance.c \
../Core/Src/SubStatemachine_bat3_Maintenance.c \
../Core/Src/Timer_function.c \
../Core/Src/bat1_asoc.c \
../Core/Src/bat2_asoc.c \
../Core/Src/bat3_asoc.c \
../Core/Src/main.c \
../Core/Src/stm32f7xx_hal_msp.c \
../Core/Src/stm32f7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f7xx.c \
../Core/Src/timer_delay.c 

OBJS += \
./Core/Src/Bat1_Maint_SPCI_RTE.o \
./Core/Src/Bat1_Update_Info_during_Maintenance.o \
./Core/Src/Bat2_Update_Info_during_Maintenance.o \
./Core/Src/Bat3_Update_Info_during_Maintenance.o \
./Core/Src/Battery1_Maintenance_General_Info.o \
./Core/Src/Battery1_Maintenance_Specific_Info.o \
./Core/Src/Battery2_Maintenance_General_Info.o \
./Core/Src/Battery3_Maintenance_General_Info.o \
./Core/Src/Commands_from_Raspi_To_STM32.o \
./Core/Src/Handle_Gpio_pins.o \
./Core/Src/Results_Auto_Test_Bat1_Maintenance.o \
./Core/Src/Results_Auto_Test_Bat2_Maintenance.o \
./Core/Src/Results_Auto_Test_Bat3_Maintenance.o \
./Core/Src/Specific_parameters_main_BAT1.o \
./Core/Src/Specific_parameters_main_BAT2.o \
./Core/Src/Specific_parameters_main_BAT3.o \
./Core/Src/SubStatemachine_bat1_Maintenance.o \
./Core/Src/SubStatemachine_bat2_Maintenance.o \
./Core/Src/SubStatemachine_bat3_Maintenance.o \
./Core/Src/Timer_function.o \
./Core/Src/bat1_asoc.o \
./Core/Src/bat2_asoc.o \
./Core/Src/bat3_asoc.o \
./Core/Src/main.o \
./Core/Src/stm32f7xx_hal_msp.o \
./Core/Src/stm32f7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f7xx.o \
./Core/Src/timer_delay.o 

C_DEPS += \
./Core/Src/Bat1_Maint_SPCI_RTE.d \
./Core/Src/Bat1_Update_Info_during_Maintenance.d \
./Core/Src/Bat2_Update_Info_during_Maintenance.d \
./Core/Src/Bat3_Update_Info_during_Maintenance.d \
./Core/Src/Battery1_Maintenance_General_Info.d \
./Core/Src/Battery1_Maintenance_Specific_Info.d \
./Core/Src/Battery2_Maintenance_General_Info.d \
./Core/Src/Battery3_Maintenance_General_Info.d \
./Core/Src/Commands_from_Raspi_To_STM32.d \
./Core/Src/Handle_Gpio_pins.d \
./Core/Src/Results_Auto_Test_Bat1_Maintenance.d \
./Core/Src/Results_Auto_Test_Bat2_Maintenance.d \
./Core/Src/Results_Auto_Test_Bat3_Maintenance.d \
./Core/Src/Specific_parameters_main_BAT1.d \
./Core/Src/Specific_parameters_main_BAT2.d \
./Core/Src/Specific_parameters_main_BAT3.d \
./Core/Src/SubStatemachine_bat1_Maintenance.d \
./Core/Src/SubStatemachine_bat2_Maintenance.d \
./Core/Src/SubStatemachine_bat3_Maintenance.d \
./Core/Src/Timer_function.d \
./Core/Src/bat1_asoc.d \
./Core/Src/bat2_asoc.d \
./Core/Src/bat3_asoc.d \
./Core/Src/main.d \
./Core/Src/stm32f7xx_hal_msp.d \
./Core/Src/stm32f7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f7xx.d \
./Core/Src/timer_delay.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

