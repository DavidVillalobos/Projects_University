OBJS = main.o Gato.o in_out.o jugador.o tablero.o
SOURCE = main.cpp Gato.cpp in_out.cpp jugador.cpp tablero.cpp
HEADER = Gato.h in_out.h jugador.h tablero.h
OUT = main.exe
CC = g++
FLAGS = -c -g -Wall
LFLAGS =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

Gato.o: Gato.cpp
	$(CC) $(FLAGS) Gato.cpp

in_out.o: in_out.cpp
	$(CC) $(FLAGS) in_out.cpp

jugador.o: jugador.cpp
	$(CC) $(FLAGS) jugador.cpp

tablero.o: tablero.cpp
	$(CC) $(FLAGS) tablero.cpp

clean:
	del $(OBJS) $(OUT)

run: $(OUT)
	$(OUT)
