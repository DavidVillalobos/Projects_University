"""
        Universidad Nacional
        Facultad de Ciencias Exactas y Naturales
        Escuela de Informática
        EIF207 – Estructuras de Datos
        II Proyecto Analizador Semantico
        Profesor: José Pablo Calvo Suárez
        Alumno: Luis David Villalobos Gonzalez
"""
import sys
from Classes.AnalizadorSemantico import AnalizadorSemantico

def do_test(path):
    print("  TESTING --> " + path)
    print(AnalizadorSemantico(path).compileCode())

if __name__ == "__main__":
    argv = sys.argv
    if len(argv) == 1:
        #tests
        do_test("Tests/Example1.txt")
        do_test("Tests/Example2.txt")
        do_test("Tests/Example3.txt")
    elif len(argv) == 2:
        do_test(argv[1])
    input("Press any key to continue . . .")