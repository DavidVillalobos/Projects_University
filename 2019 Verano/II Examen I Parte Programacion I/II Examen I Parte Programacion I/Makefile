OBJS = main.o Paciente_General.o Paciente_Geriatria.o Paciente_Pediatria.o TipoPaciente.o
SOURCE = main.cpp Paciente_General.cpp Paciente_Geriatria.cpp Paciente_Pediatria.cpp TipoPaciente.cpp
HEADER = Paciente_General.h Paciente_Geriatria.h Paciente_Pediatria.h TipoPaciente.h
OUT = main.exe
CC = g++
FLAGS = -c -g -Wall
LFLAGS =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

Paciente_General.o: Paciente_General.cpp
	$(CC) $(FLAGS) Paciente_General.cpp

Paciente_Geriatria.o: Paciente_Geriatria.cpp
	$(CC) $(FLAGS) Paciente_Geriatria.cpp

Paciente_Pediatria.o: Paciente_Pediatria.cpp
	$(CC) $(FLAGS) Paciente_Pediatria.cpp

TipoPaciente.o: TipoPaciente.cpp
	$(CC) $(FLAGS) TipoPaciente.cpp

clean:
	del $(OBJS) $(OUT)

run: $(OUT)
	$(OUT)
