OBJS = main.o simulation.o
SOURCE = main.c simulation.c
HEADER = simulation.h
OUT	= program
CC = gcc
FLAGS = -g -c -Wall
LFLAGS = -pthread -lm

all: clean $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c

simulation.o: simulation.c
	$(CC) $(FLAGS) simulation.c

clean:
	rm -f $(OBJS) $(OUT)