OBJS = main.o Contrato.o Controlador.o Empleado.o Empresa.o Error.o Fecha.o In_Out.o Lista.o Nodo.o ObjetoBase.o Planilla.o PlanillaCorta.o PlanillaIdefinida.o Plaza.o Profesional.o Puesto.o
SOURCE = main.cpp Contrato.cpp Controlador.cpp Empleado.cpp Empresa.cpp Error.cpp Fecha.cpp In_Out.cpp Lista.cpp Nodo.cpp ObjetoBase.cpp Planilla.cpp PlanillaCorta.cpp PlanillaIdefinida.cpp Plaza.cpp Profesional.cpp Puesto.cpp
HEADER = Contrato.h Controlador.h Empleado.h Empresa.h Error.h Fecha.h In_Out.h Lista.h Nodo.h ObjetoBase.h Planilla.h PlanillaCorta.h PlanillaIdefinida.h Plaza.h Profesional.h Puesto.h
OUT = main.exe
CC = g++
FLAGS = -c -g -Wall
LFLAGS =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

Contrato.o: Contrato.cpp
	$(CC) $(FLAGS) Contrato.cpp

Controlador.o: Controlador.cpp
	$(CC) $(FLAGS) Controlador.cpp

Empleado.o: Empleado.cpp
	$(CC) $(FLAGS) Empleado.cpp

Empresa.o: Empresa.cpp
	$(CC) $(FLAGS) Empresa.cpp

Error.o: Error.cpp
	$(CC) $(FLAGS) Error.cpp

Fecha.o: Fecha.cpp
	$(CC) $(FLAGS) Fecha.cpp

In_Out.o: In_Out.cpp
	$(CC) $(FLAGS) In_Out.cpp

Lista.o: Lista.cpp
	$(CC) $(FLAGS) Lista.cpp

Nodo.o: Nodo.cpp
	$(CC) $(FLAGS) Nodo.cpp

ObjetoBase.o: ObjetoBase.cpp
	$(CC) $(FLAGS) ObjetoBase.cpp

Planilla.o: Planilla.cpp
	$(CC) $(FLAGS) Planilla.cpp

PlanillaCorta.o: PlanillaCorta.cpp
	$(CC) $(FLAGS) PlanillaCorta.cpp

PlanillaIdefinida.o: PlanillaIdefinida.cpp
	$(CC) $(FLAGS) PlanillaIdefinida.cpp

Plaza.o: Plaza.cpp
	$(CC) $(FLAGS) Plaza.cpp

Profesional.o: Profesional.cpp
	$(CC) $(FLAGS) Profesional.cpp

Puesto.o: Puesto.cpp
	$(CC) $(FLAGS) Puesto.cpp
	
clean:
	del $(OBJS) $(OUT)

run: $(OUT)
	$(OUT)
