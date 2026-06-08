################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Buttons.c \
../Src/Delay.c \
../Src/Interrupt.c \
../Src/UART.c \
../Src/main.c \
../Src/ringBuffer.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/Buttons.o \
./Src/Delay.o \
./Src/Interrupt.o \
./Src/UART.o \
./Src/main.o \
./Src/ringBuffer.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/Buttons.d \
./Src/Delay.d \
./Src/Interrupt.d \
./Src/UART.d \
./Src/main.d \
./Src/ringBuffer.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/Buttons.cyclo ./Src/Buttons.d ./Src/Buttons.o ./Src/Buttons.su ./Src/Delay.cyclo ./Src/Delay.d ./Src/Delay.o ./Src/Delay.su ./Src/Interrupt.cyclo ./Src/Interrupt.d ./Src/Interrupt.o ./Src/Interrupt.su ./Src/UART.cyclo ./Src/UART.d ./Src/UART.o ./Src/UART.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/ringBuffer.cyclo ./Src/ringBuffer.d ./Src/ringBuffer.o ./Src/ringBuffer.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

