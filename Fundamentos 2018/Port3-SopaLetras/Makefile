OBJS = main.o
SOURCE = main.cpp Letras.cpp
HEADER = Letras.h
OUT = main.exe
CC = g++
FLAGS = -c -g
LFLAGS =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

Letras.o: Letras.cpp
	$(CC) $(FLAGS) Letras.cpp

clean:
	del $(OBJS) $(OUT)

run: $(OUT)
	$(OUT)
