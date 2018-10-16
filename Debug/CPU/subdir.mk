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

C_SRCS += \
../CPU/InstructionDecode.c

C_SRCS += \
../CPU/InstructionIssue.c

C_SRCS += \
../CPU/InstructionExecute.c

C_SRCS += \
../CPU/InstructionCommit.c

OBJS += \
./CPU/CPU.o

OBJS += \
./CPU/ReadConfig.o

OBJS += \
./CPU/InstructionDecode.o

OBJS += \
./CPU/InstructionFetch.o

OBJS += \
./CPU/InstructionIssue.o

OBJS += \
./CPU/InstructionExecute.o

OBJS += \
./CPU/InstructionCommit.o

C_DEPS += \
./CPU/CPU.d


# Each subdirectory must supply rules for building sources it contributes
CPU/%.o: ../CPU/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
