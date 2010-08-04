################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../conjdis.c \
../grafo.c \
../heap.c \
../interface.c \
../main.c \
../mensagens.c \
../opengl.c \
../sinais.c 

OBJS += \
./conjdis.o \
./grafo.o \
./heap.o \
./interface.o \
./main.o \
./mensagens.o \
./opengl.o \
./sinais.o 

C_DEPS += \
./conjdis.d \
./grafo.d \
./heap.d \
./interface.d \
./main.d \
./mensagens.d \
./opengl.d \
./sinais.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include/gtkglext-1.0 -I/usr/include/gtk-2.0 -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -O0 -g3 -Wall -c -fmessage-length=0 `pkg-config --cflags gtkglext-1.0` -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


