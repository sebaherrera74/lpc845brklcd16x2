################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/LPC845_Project3.c \
../source/digital.c \
../source/mtb.c \
../source/semihost_hardfault.c 

OBJS += \
./source/LPC845_Project3.o \
./source/digital.o \
./source/mtb.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/LPC845_Project3.d \
./source/digital.d \
./source/mtb.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_LPC845M301JBD48 -DCPU_LPC845M301JBD48_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/board" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/source" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/drivers" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/device" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/CMSIS" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/component/uart" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/utilities" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/component/timer" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/component/gpio" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/component/timer_manager" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/component/lists" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/component/led" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/component/button" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


