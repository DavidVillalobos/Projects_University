OBJS = main.o diccionario.o ficha.o in_out.o juego.o jugador.o listaDiccionario.o listaPalabras.o palabra.o tablero.o
SOURCE = main.cpp diccionario.cpp ficha.cpp in_out.cpp juego.cpp jugador.cpp listaDiccionario.cpp listaPalabras.cpp palabra.cpp tablero.cpp
HEADER = diccionario.h ficha.h in_out.h juego.h jugador.h listaDiccionario.h listaPalabras.h palabra.h tablero.h
OUT = main.exe
CC = g++
FLAGS = -c -g -Wall
LFLAGS =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

diccionario.o: diccionario.cpp
	$(CC) $(FLAGS) diccionario.cpp

ficha.o: ficha.cpp
	$(CC) $(FLAGS) ficha.cpp

in_out.o: in_out.cpp
	$(CC) $(FLAGS) in_out.cpp

juego.o: juego.cpp
	$(CC) $(FLAGS) juego.cpp

jugador.o: jugador.cpp
	$(CC) $(FLAGS) jugador.cpp

listaDiccionario.o: listaDiccionario.cpp
	$(CC) $(FLAGS) listaDiccionario.cpp

listaPalabras.o: listaPalabras.cpp
	$(CC) $(FLAGS) listaPalabras.cpp

palabra.o: palabra.cpp
	$(CC) $(FLAGS) palabra.cpp

tablero.o: tablero.cpp
	$(CC) $(FLAGS) tablero.cpp

clean:
	del $(OBJS) $(OUT)

run: $(OUT)
	$(OUT)
