################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../conjdis.c \
../estruturas.c \
../grafo.c \
../heap.c \
../importar.c \
../interface.c \
../main.c \
../mapa.c \
../mensagens.c \
../opengl.c \
../ponto.c \
../selecionarArquivo.c \
../sinais.c \
../util.c 

OBJS += \
./conjdis.o \
./estruturas.o \
./grafo.o \
./heap.o \
./importar.o \
./interface.o \
./main.o \
./mapa.o \
./mensagens.o \
./opengl.o \
./ponto.o \
./selecionarArquivo.o \
./sinais.o \
./util.o 

C_DEPS += \
./conjdis.d \
./estruturas.d \
./grafo.d \
./heap.d \
./importar.d \
./interface.d \
./main.d \
./mapa.d \
./mensagens.d \
./opengl.d \
./ponto.d \
./selecionarArquivo.d \
./sinais.d \
./util.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include/gtkglext-1.0 -I/usr/include/glib-2.0 -I/usr/include/pango-1.0 -I/usr/include/gtk-2.0 -O0 -g3 -Wall -c -fmessage-length=0 `pkg-config --cflags gtkglext-1.0` -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


