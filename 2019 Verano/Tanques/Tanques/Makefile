OBJS = main.o bala.o in_out.o juego.o jugador.o jugadores.o tanque.o
SOURCE = main.cpp bala.cpp in_out.cpp juego.cpp jugador.cpp jugadores.cpp tanque.cpp
HEADER = bala.h in_out.h juego.h jugador.h jugadores.h tanque.h
OUT = main.exe
CC = g++
FLAGS = -c -g -Wall
LFLAGS =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

bala.o: bala.cpp
	$(CC) $(FLAGS) bala.cpp

in_out.o: in_out.cpp
	$(CC) $(FLAGS) in_out.cpp

juego.o: juego.cpp
	$(CC) $(FLAGS) juego.cpp

jugador.o: jugador.cpp
	$(CC) $(FLAGS) jugador.cpp

jugadores.o: jugadores.cpp
	$(CC) $(FLAGS) jugadores.cpp

tanque.o: tanque.cpp
	$(CC) $(FLAGS) tanque.cpp

clean:
	del $(OBJS) $(OUT)

run: $(OUT)
	$(OUT)
