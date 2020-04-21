OBJS	= main.o Sector.o Simulation.o
SOURCE	= main.c Sector.c Simulation.c
HEADER	= Sector.h Simulation.h
OUT	= start
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = -pthread -lm

all: clean $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c

Sector.o: Sector.c
	$(CC) $(FLAGS) Sector.c

Simulation.o: Simulation.c
	$(CC) $(FLAGS) Simulation.c

clean:
	rm -f $(OBJS) $(OUT)