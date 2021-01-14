OBJS = main.o
SOURCE = main.cpp .cpp
HEADER =
OUT = main.exe
CC = g++
FLAGS = -c -g -Wall
LFLAGS =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

clean:
	del $(OBJS) $(OUT)

run: $(OUT)
	$(OUT)
