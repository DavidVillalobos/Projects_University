OBJS = Principal.o
SOURCE = Principal.cpp
HEADER =
OUT = main.exe
CC = g++
FLAGS = -c -g -Wall
LFLAGS =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Principal.o: Principal.cpp
	$(CC) $(FLAGS) Principal.cpp

clean:
	del $(OBJS) $(OUT)

run: $(OUT)
	$(OUT)
