"""
                LABORATORIO EXTRA
        
        Autor: XXXXXXXXXX
        Fecha:  XX/XX/XX
"""
import numpy as np

print(" 1 Ejercicio, crear una matriz indentidad 20X20")
# Existe una funcion en la libreria Numpy la cual crea
# una matrix identidad, ella recibe por parametro la
# dimension de la matriz
print(np.identity(20))

print("Ejercicio 2, crear un metodo, que verifica si una matriz es")
print("antisimetrica o simetrica")
def foo(matriz): # . . . No hay nombre expecificado para el metodo por ello utilice uno trivial
    if isinstance(matriz, list):
        symmetrical = True# Variable booleana para verificar si es simetrica
        for row in range(len(matriz)): # Por cada fila en la matrix
            for col in range(len(matriz)):# Por cada columna de las filas
                # No hace falta revisar la diagonal principal, por ello solamente revisar
                # los elementos cuya fila y columna sean diferentes
                # si un elemento es diferente al que le corresponde en simetria
                # la matriz deja de ser simetrica, porque deben de ser iguales
                if row != col and matriz[row][col] != matriz[col][row]:
                    symmetrical = False
                    # Aunque la matriz no sea simetrica puede ser antisimetrica si el elemento 
                    # al que corresponde en simetria es el mismo pero con su signo contrario
                    if matriz[row][col] != -matriz[col][row]:
                        # De no ser asi no es simetrica ni antisimetrica
                        return 0# por lo que se debe retornar 0
        # si la variable symetrical aun es True, la matriz es simetrica 
        # de no ser asi es antisimetrica 
        return 1 if symmetrical else -1
    elif not isinstance(matriz, int) and not isinstance(matriz, str):
        try:# Aqui el indexado es una tupla porque asi lo exigen los arreglos y matrices de numpy 
            symmetrical = True # la unica diferencia entre el modo anterior es el indexado de la lista
            for row in range(len(matriz)):
                for col in range(len(matriz)): 
                    if row != col and matriz[row, col] != matriz[col, row]:
                        symmetrical = False            
                        if matriz[row, col] != -matriz[col, row]:
                            return 0
            return 1 if symmetrical else -1
        except: # Con ayuda del try y except podemos validar por si se recibe un objeto 
          #desconocido una clase la cual puede generar excepciones 
          return'El metodo foo(matriz) debe recibir unicamente una matriz por parametro ya sea de tipo lista o arreglo bidimensional de numpy'
    else: return'La matriz que recibe foo(matriz) no puede ser de tipo entero o un string, debe ser una lista o arreglo bidimensional'

print("Algunos casos de prueba de foo(matriz)")
print("1) Simetrica:",foo(np.matrix(np.identity(20))))
print("2) AntiSimetrica:",foo(np.array([[1,2,3],[-2,3,4],[-3,-4,0]])))
print("3) Error: ",foo('[[1,2],[2,1]]'))
print("4) Caso Contrario",foo(np.matrix([[1,6,3],[-2,5,4],[-3,-4,4]])))
print("5) AntiSimetrica:",foo(np.matrix([[ 12,2,3,10],[ -2,45,-8,32],[ -3,8,56,-0],[ -10,-32,0,43]])))
print("6) Simetrica",foo([[1,6],[6,1]]))
print("7) Caso Contrario",foo(np.matrix([[1,6],[7,1]])))
print("8) Error",foo(7892))

print("Ejercicio 3, crear un matriz 20X20 solamente con 1´s")
# Existe una funcion en Numpy la cual crea una matriz solamente
# con 1´s, para ello recibe por parametro la cantidad de filas y columnas
print(np.ones((20, 20)))