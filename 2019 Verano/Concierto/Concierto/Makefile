OBJS	= Control.o Gimnasio.o in_out.o tiquete.o principal.o
SOURCE	= Control.cpp Gimnasio.cpp in_out.cpp tiquete.cpp principal.cpp
HEADER	= Control.h Gimnasio.h in_out.h tiquete.h
OUT	= main.exe
CC	 = g++
FLAGS	 = -c
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

principal.o: principal.cpp
	$(CC) $(FLAGS) principal.cpp

Control.o: Control.cpp
	$(CC) $(FLAGS) Control.cpp
	
Gimnasio.o: Gimnasio.cpp
	$(CC) $(FLAGS) Gimnasio.cpp
	
in_out.o: in_out.cpp
	$(CC) $(FLAGS) in_out.cpp

tiquete.o: tiquete.cpp
	$(CC) $(FLAGS) tiquete.cpp

clean:
	del $(OBJS) $(OUT)

run: $(OUT)
	$(OUT)