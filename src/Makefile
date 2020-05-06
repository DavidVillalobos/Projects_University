OBJS	= main.o 
SOURCE	= main.c 
HEADER	= 
OUT	= program
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = -pthread -lm

all: clean $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c

clean:
	rm -f $(OBJS) $(OUT)
