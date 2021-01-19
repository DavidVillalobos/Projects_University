OBJS = principal.o avion.o coleccionRuta.o coleccionVuelo.o control.o hangar.o in_out.o pasajero.o ruta.o tiquete.o vuelo.o
SOURCE = principal.cpp avion.cpp coleccionRuta.cpp coleccionVuelo.cpp control.cpp hangar.cpp in_out.cpp pasajero.cpp ruta.cpp tiquete.cpp vuelo.cpp
HEADER = avion.h coleccionRuta.h coleccionVuelo.h control.h hangar.h in_out.h pasajero.h ruta.h tiquete.h vuelo.h
OUT = main.exe
CC = g++
FLAGS = -c -g -Wall
LFLAGS =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

principal.o: principal.cpp
	$(CC) $(FLAGS) principal.cpp

avion.o: avion.cpp
	$(CC) $(FLAGS) avion.cpp

coleccionRuta.o: coleccionRuta.cpp
	$(CC) $(FLAGS) coleccionRuta.cpp

coleccionVuelo.o: coleccionVuelo.cpp
	$(CC) $(FLAGS) coleccionVuelo.cpp

control.o: control.cpp
	$(CC) $(FLAGS) control.cpp

hangar.o: hangar.cpp
	$(CC) $(FLAGS) hangar.cpp

in_out.o: in_out.cpp
	$(CC) $(FLAGS) in_out.cpp

pasajero.o: pasajero.cpp
	$(CC) $(FLAGS) pasajero.cpp

ruta.o: ruta.cpp
	$(CC) $(FLAGS) ruta.cpp

tiquete.o: tiquete.cpp
	$(CC) $(FLAGS) tiquete.cpp

vuelo.o: vuelo.cpp
	$(CC) $(FLAGS) vuelo.cpp

clean:
	del $(OBJS) $(OUT)

run: $(OUT)
	$(OUT)
