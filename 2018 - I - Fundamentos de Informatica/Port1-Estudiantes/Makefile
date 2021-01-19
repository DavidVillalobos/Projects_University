OBJS = Main.o
SOURCE = Main.cpp Estudiantes.cpp
HEADER = Estudiantes.h
OUT = main.exe
CC = g++
FLAGS = -c -g -Wall
LFLAGS =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Main.o: Main.cpp
	$(CC) $(FLAGS) Main.cpp

Estudiantes.o: Estudiantes.cpp
	$(CC) $(FLAGS) Estudiantes.cpp

clean:
	del $(OBJS) $(OUT)

run: $(OUT)
	$(OUT)
