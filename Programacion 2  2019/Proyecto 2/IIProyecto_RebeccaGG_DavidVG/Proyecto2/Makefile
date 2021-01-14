OBJS = Principal.o Aleatoria.o Arbol.o Estrategia.o Ficha.o Gane.o In_Out.o Juego.o Movimiento.o Nodo.o Ofensiva.o Posicion.o Tablero.o
SOURCE = Principal.cpp Aleatoria.cpp Arbol.cpp Estrategia.cpp Ficha.cpp Gane.cpp In_Out.cpp Juego.cpp Movimiento.cpp Nodo.cpp Ofensiva.cpp Posicion.cpp Tablero.cpp
HEADER = Aleatoria.h Arbol.h Estrategia.h Ficha.h Gane.h In_Out.h Juego.h Movimiento.h Nodo.h Ofensiva.h Posicion.h Tablero.h
OUT = main.exe
CC = g++
FLAGS = -c -g -Wall
LFLAGS =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Principal.o: Principal.cpp
	$(CC) $(FLAGS) Principal.cpp

Aleatoria.o: Aleatoria.cpp
	$(CC) $(FLAGS) Aleatoria.cpp

Arbol.o: Arbol.cpp
	$(CC) $(FLAGS) Arbol.cpp

Estrategia.o: Estrategia.cpp
	$(CC) $(FLAGS) Estrategia.cpp

Ficha.o: Ficha.cpp
	$(CC) $(FLAGS) Ficha.cpp

Gane.o: Gane.cpp
	$(CC) $(FLAGS) Gane.cpp

In_Out.o: In_Out.cpp
	$(CC) $(FLAGS) In_Out.cpp

Juego.o: Juego.cpp
	$(CC) $(FLAGS) Juego.cpp

Movimiento.o: Movimiento.cpp
	$(CC) $(FLAGS) Movimiento.cpp

Nodo.o: Nodo.cpp
	$(CC) $(FLAGS) Nodo.cpp

Ofensiva.o: Ofensiva.cpp
	$(CC) $(FLAGS) Ofensiva.cpp

Posicion.o: Posicion.cpp
	$(CC) $(FLAGS) Posicion.cpp

Tablero.o: Tablero.cpp
	$(CC) $(FLAGS) Tablero.cpp

clean:
	del $(OBJS) $(OUT)

run: $(OUT)
	$(OUT)
