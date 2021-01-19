
JFLAGS = -g
JC = javac 

.SUFFIXES: .java .class

.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
        Estudiante.java \
        Curso.java \
        Universidad.java \
        Model.java \
        Controller.java \
        FileManager.java \
        View.java \
        Main.java

all: $(CLASSES:.java=.class)

run: 
	java -cp . Main

clean:
	del $(CLASSES:.java=.class)
