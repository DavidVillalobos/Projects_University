OBJS	= main.o Vehicle.o Semaforo.o Sector.o Officer.o Queue.o Simulation.o
SOURCE	= main.c Vehicle.c Semaforo.c Sector.c Officer.c Queue.c Simulation.c
HEADER	= Vehicle.h Semaforo.h Sector.h Officer.h Queue.h Simulation.h
OUT	= out
CC	 = gcc
FLAGS	 = -g -c -Wall -pedantic -ggdb --debug
LFLAGS	 = -pthread -lm

all: clean $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)


main.o: main.c
	$(CC) $(FLAGS) main.c

Vehicle.o: Vehicle.c
	$(CC) $(FLAGS) Vehicle.c

Semaforo.o: Semaforo.c
	$(CC) $(FLAGS) Semaforo.c

Sector.o: Sector.c
	$(CC) $(FLAGS) Sector.c

Officer.o: Officer.c
	$(CC) $(FLAGS) Officer.c

Queue.o: Queue.c
	$(CC) $(FLAGS) Queue.c

Simulation.o: Simulation.c
	$(CC) $(FLAGS) Simulation.c

clean:
	rm -f $(OBJS) $(OUT)