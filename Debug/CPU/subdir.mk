################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CPU/CPU.c

C_SRCS += \
../CPU/ReadConfig.c

C_SRCS += \
../CPU/InstructionFetch.c

OBJS += \
./CPU/CPU.o

OBJS += \
./CPU/ReadConfig.o

OBJS += \
./CPU/InstructionFetch.o

C_DEPS += \
./CPU/CPU.d 


# Each subdirectory must supply rules for building sources it contributes
CPU/%.o: ../CPU/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


