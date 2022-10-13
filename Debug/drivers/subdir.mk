################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_ctimer.c \
../drivers/fsl_gpio.c \
../drivers/fsl_inputmux.c \
../drivers/fsl_pint.c \
../drivers/fsl_power.c \
../drivers/fsl_reset.c \
../drivers/fsl_spi.c \
../drivers/fsl_swm.c \
../drivers/fsl_syscon.c \
../drivers/fsl_usart.c 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_ctimer.o \
./drivers/fsl_gpio.o \
./drivers/fsl_inputmux.o \
./drivers/fsl_pint.o \
./drivers/fsl_power.o \
./drivers/fsl_reset.o \
./drivers/fsl_spi.o \
./drivers/fsl_swm.o \
./drivers/fsl_syscon.o \
./drivers/fsl_usart.o 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_ctimer.d \
./drivers/fsl_gpio.d \
./drivers/fsl_inputmux.d \
./drivers/fsl_pint.d \
./drivers/fsl_power.d \
./drivers/fsl_reset.d \
./drivers/fsl_spi.d \
./drivers/fsl_swm.d \
./drivers/fsl_syscon.d \
./drivers/fsl_usart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_LPC845M301JBD48 -DCPU_LPC845M301JBD48_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/board" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/source" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/drivers" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/device" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/CMSIS" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/component/uart" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/utilities" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/component/timer" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/component/gpio" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/component/timer_manager" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/component/lists" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/component/led" -I"/home/sebastian/Documents/MCUXpresso_11.2.1_4149/workspace/proyectos/pinesIO/component/button" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


