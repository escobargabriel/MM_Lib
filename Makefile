# GNU Makefile

CC = gcc
CCFLAGS = -Wall -O3 #-llikwid #-funroll-all-loops
LDFLAGS = -pthread #-pg
TARGET = main_matriz gera_matriz2 help
EXE = ./gera_matriz2

all: $(TARGET)

%.o: %.c
		$(CC) $(CCFLAGS) -c $<

%: %.o
		$(CC) $(LDFLAGS) $^ -o $@

main_matriz: main_matriz.c matriz.o toolsv2.o matriz-operacoes.o matriz-operacoes-threads.o
		$(CC) $(CCFLAGS) matriz-operacoes-threads.o matriz-operacoes.o matriz.o toolsv2.o main_matriz.c -o $@ $(LDFLAGS)

gera_matriz2: matriz.o toolsv2.o gera_matriz2.c
		$(CC) $(CCFLAGS) matriz.o toolsv2.o gera_matriz2.c -o $@ $(LDFLAGS)

help:
		@echo "IMPORTANTE: LEIA O ARQUIVO README E OBSERVE AS RESTRIÇÕES DO SISTEMA!"
		@echo "Caso não sejam respeitadas as restrições não é garantido o funcionamento da aplicação para algumas funções!"
		@echo "####### Exemplo de Execução #######"
		@echo "./main_matriz 128x128-mat.map 128x128-mat1.map 2"

clean:
		rm -f *.o *~ $(TARGET) *.map *.map-result

