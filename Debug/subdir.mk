################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../acessibilidade.c \
../classificacao.c \
../conexoes.c \
../conjdis.c \
../dijkstra.c \
../editar.c \
../estruturas.c \
../grafo.c \
../heap.c \
../importar.c \
../interface.c \
../main.c \
../mapa.c \
../math2.c \
../mensagens.c \
../opengl.c \
../ponto.c \
../projeto.c \
../selecionarArquivo.c \
../sqlite3.c \
../util.c 

OBJS += \
./acessibilidade.o \
./classificacao.o \
./conexoes.o \
./conjdis.o \
./dijkstra.o \
./editar.o \
./estruturas.o \
./grafo.o \
./heap.o \
./importar.o \
./interface.o \
./main.o \
./mapa.o \
./math2.o \
./mensagens.o \
./opengl.o \
./ponto.o \
./projeto.o \
./selecionarArquivo.o \
./sqlite3.o \
./util.o 

C_DEPS += \
./acessibilidade.d \
./classificacao.d \
./conexoes.d \
./conjdis.d \
./dijkstra.d \
./editar.d \
./estruturas.d \
./grafo.d \
./heap.d \
./importar.d \
./interface.d \
./main.d \
./mapa.d \
./math2.d \
./mensagens.d \
./opengl.d \
./ponto.d \
./projeto.d \
./selecionarArquivo.d \
./sqlite3.d \
./util.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include/gtkglext-1.0 -I/usr/include/glib-2.0 -I/usr/include/pango-1.0 -I/usr/include/gtk-2.0 -O0 -g3 -Wall -c -fmessage-length=0 `pkg-config --cflags gtkglext-1.0` -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


