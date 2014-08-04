################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../dictTest.cpp \
../f.cpp \
../g.cpp \
../main.cpp \
../matrixProduct.cpp \
../multiGame.cpp \
../someSum.cpp \
../template.cpp 

OBJS += \
./dictTest.o \
./f.o \
./g.o \
./main.o \
./matrixProduct.o \
./multiGame.o \
./someSum.o \
./template.o 

CPP_DEPS += \
./dictTest.d \
./f.d \
./g.d \
./main.d \
./matrixProduct.d \
./multiGame.d \
./someSum.d \
./template.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


