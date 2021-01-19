OBJS = main.o Exception.o Integer.o Nodo.o
SOURCE = main.cpp Exception.cpp Integer.cpp Nodo.cpp
HEADER = Exception.h Integer.h Nodo.h
OUT = main.exe
CC = g++
FLAGS = -c -g -Wall
LFLAGS =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

Exception.o: Exception.cpp
	$(CC) $(FLAGS) Exception.cpp

Integer.o: Integer.cpp
	$(CC) $(FLAGS) Integer.cpp

Nodo.o: Nodo.cpp
	$(CC) $(FLAGS) Nodo.cpp

clean:
	del $(OBJS) $(OUT)

run: $(OUT)
	$(OUT)
