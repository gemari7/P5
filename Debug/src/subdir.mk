################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/QAPEvaluator.cpp \
../src/QAPInstance.cpp \
../src/QAPSolGenerator.cpp \
../src/QAPSolution.cpp \
../src/Timer.cpp \
../src/main.cpp \
../src/seeds.cpp 

OBJS += \
./src/QAPEvaluator.o \
./src/QAPInstance.o \
./src/QAPSolGenerator.o \
./src/QAPSolution.o \
./src/Timer.o \
./src/main.o \
./src/seeds.o 

CPP_DEPS += \
./src/QAPEvaluator.d \
./src/QAPInstance.d \
./src/QAPSolGenerator.d \
./src/QAPSolution.d \
./src/Timer.d \
./src/main.d \
./src/seeds.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/i52gaorg/Desktop/meta/P4Metaheuristics/src/include" -O0 -g3 -pg -pedantic -pedantic-errors -Wall -Wextra -Werror -Wconversion -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


