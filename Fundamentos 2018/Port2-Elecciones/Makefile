OBJS = main.o
SOURCE = main.cpp Elecciones.cpp
HEADER = Elecciones.h
OUT = main.exe
CC = g++
FLAGS = -c -g -Wall
LFLAGS =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

Elecciones.o: Elecciones.cpp
	$(CC) $(FLAGS) Elecciones.cpp

clean:
	del $(OBJS) $(OUT)

run: $(OUT)
	$(OUT)
