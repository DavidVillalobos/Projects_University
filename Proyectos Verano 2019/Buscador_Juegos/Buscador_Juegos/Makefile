OBJS	= Control.o etiqueta.o etiquetas.o in_out.o juego.o juegos.o main.o
SOURCE	= Control.cpp etiqueta.cpp etiquetas.cpp in_out.cpp juego.cpp juegos.cpp main.cpp
HEADER	= Control.h etiqueta.h etiquetas.h in_out.h juego.h juegos.h
OUT	= main.exe
CC	 = g++
FLAGS	 = -c
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

Control.o: Control.cpp
	$(CC) $(FLAGS) Control.cpp
	
etiqueta.o: etiqueta.cpp
	$(CC) $(FLAGS) etiqueta.cpp

etiquetas.o: etiquetas.cpp
	$(CC) $(FLAGS) etiquetas.cpp

in_out.o: in_out.cpp
	$(CC) $(FLAGS) in_out.cpp

juego.o: juego.cpp
	$(CC) $(FLAGS) juego.cpp

juegos.o: juegos.cpp
	$(CC) $(FLAGS) juegos.cpp

clean:
	del $(OBJS) $(OUT)

run: $(OUT)
	$(OUT)