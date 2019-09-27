from proyecto import *
import csv
resultados = []
with open('Prueba1.csv','r') as file_Pruebas:
    reader = csv.reader(file_Pruebas, delimiter=';')
    for fila in reader:
        try:
            resp = solve(fila[0]) == int(fila[1])
            resultados.append((fila[0],fila[1],resp))
        except:
            print("Error de sintaxis en: ",fila[0])
file_Pruebas.close()
for resul in resultados:
    print(resul)