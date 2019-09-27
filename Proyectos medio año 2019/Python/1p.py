"""#1) Ejercicio de matrices

#Existe una tienda la cual tiene las ventas
#de cada dia del mes en un archivo matriz.txt
#cada fila representa una semana y cada columna 
#un dia de la semana de lunes a viernes
#se necesita saber cual semana tuvo mayor y
#menor ventas en promedio
with open("matriz.txt","r") as file_matriz:
    j = 0
    matriz = []
     L  M  K  J  V
    1	[ ][ ][ ][ ][ ]
    2   [ ][ ][ ][ ][ ]
    3   [ ][ ][ ][ ][ ] 
    for linea in file_matriz.readlines():
        matriz.append([])
        for valor in linea.split(","):
            matriz[j].append(int(valor))
        j += 1
file_matriz.close()
promedios = []
for row in matriz:
    promedio = 0
    for column in row:
        promedio += column
    promedios.append(promedio/len(row))
print(promedios)
print("El que tuvo mas ventas del mes fue la semana: ",promedios.index(max(promedios)))
print("El que tuvo menor ventas del mes fue la semana: ",promedios.index(min(promedios)))

#2) Ejercicio en un archivo notas.csv
# se tiene las notas de los estudiantes con la
# informacion de cada uno
# se necesita saber un promedio general del grupo
# ademas de cual fue el estudiante que obtuvo
# mayor y menor promedio y una lista de quienes 
# fueron aplazados, aprobados y reprobados
class Estudiante:
    def __init__(self,nombre,apellido,edad,notas):
        self.nombre = nombre
        self.apellido = apellido
        self.edad = edad
        self.notas = notas
    def promedio(self):
        prom = 0
        for nota in self.notas:
            prom += nota
        return prom/len(self.notas)
    def __str__(self):
        return f"{self.nombre} {self.apellido} {self.edad} {self.notas}"
    def __repr__(self):
        return self.__str__()
class Principios:
    def __init__(self):
        self.lista = [] 
    def insertar(self,estudiante):
        self.lista.append(estudiante)
    def imprimir(self):
        s = ""
        for estudiante in self.lista:
            s += estudiante.__str__() + "\n"
        return s
    def min(self):
        menor = self.lista[0]
        for estudiante in self.lista:
            if estudiante.promedio() < menor.promedio():
                menor = estudiante
        return menor
    def max(self):
        mayor = self.lista[0]
        for estudiante in self.lista:
            if estudiante.promedio() > mayor.promedio():
                mayor = estudiante
        return mayor
    def promedio(self):
        prom = 0
        for estudiante in self.lista:
            prom += estudiante.promedio()
        return prom/len(self.lista)
    def __str__(self):
        return self.imprimir()
    def __repr__(self):
        return self.__str__()
    def aplazados(self):
        a = []
        for estudiante in self.lista:
            if estudiante.promedio() <= 60 and estudiante.promedio() <= 69:
                a.append(estudiante)
        return a
    def aprobados(self):
        a = []
        for estudiante in self.lista:
            if estudiante.promedio() > 69:
                a.append(estudiante)
        return a
    def reprobados(self):
        a = []
        for estudiante in self.lista:
            if estudiante.promedio() <= 59:
                a.append(estudiante)
        return a
import csv   
clase = Principios()
with open("notas.csv","r") as file_notas:
    reader = csv.reader(file_notas,delimiter=";")
    aux = False
    for row in reader:
        if aux:
            clase.insertar(Estudiante(row[0],row[1],row[2],[int(row[3]),int(row[4]),int(row[5])]))
        else:
            aux = True
    clase.imprimir()
file_notas.close()"""


class Contacto:
    def __init__(self, nombre, telefono, email):
        self.nombre = nombre
        self.telefono = telefono
        self.email = email

contactos = []# Creamos la lista vacia de contactos
auxiliar = True
try:
    with open("contactos.txt","r") as file_contactos:
        for linea in file_contactos.readlines():
            informacion = linea.split(",")
            contactos.append(Contacto(informacion[0],informacion[1],informacion[2]))
    file_contactos.close()
    auxiliar = False # ya existe el archivo
except:
    print("No existe archivo previo de contactos")
    pass # si no existe el archivo no tiene que leer nada
while True :
    print("Agenda Telefonica")
    print("   1) Agregar Contacto")
    print("   2) Eliminar Contacto")
    print("   3) Mostrar Todos los Contactos")
    print("   4) Mostrar Contacto")
    print("   5) Crear Archivo")
    print("   6) Salir")
    opcion = int(input("Digite una opcion: "))
    if opcion != 6:
        if opcion == 1:
            print("Ingrese la siguiente informacion del contacto")
            nombre = input("Nombre: ")
            aux = True
            for contacto in contactos:
                if contacto.nombre == nombre:
                    aux = False
                    break
            if aux:
                telefono = input("Telefono: ")
                email = input("Email: ")
                nuevo = Contacto(nombre,telefono,email)
                contactos.append(nuevo)
                print("El contacto fue ingresado correctamente")
            else:
                print("Lo sentimos este contacto ya existe")
        elif opcion == 2:
            print("Digite el nombre del contacto a borrar")
            nombre = input("Nombre: ")
            aux1 = False
            for contacto in contactos:
                if contacto.nombre == nombre:
                    contactos.remove(contacto)
                    aux1 = True # encontrado
                    break
            if aux1:
                print("Contacto eliminado")
            else:
               print("No existe ningun contacto con este nombre")
        elif opcion == 3:
            if contactos != []:
                print("La lista de contactos")
                i = 1
                for contacto in contactos:
                    print(i,") Nombre:",contacto.nombre, "Telefono:", contacto.telefono,"Email:", contacto.email)
                    i += 1
            else:
                print("No hay contactos todavia")
        elif opcion == 4:
            print("Digite el nombre del contacto que desea ver")
            nombre = input("Nombre: ")
            for contacto in contactos:
                if contacto.nombre == nombre:
                    print(") Nombre:",contacto.nombre, "Telefono:", contacto.telefono,"Email:", contacto.email)
                    break
        elif opcion == 5:
            if auxiliar:
                print("Creando el archivo para guardar los contactos")
                with open("contactos.txt","w+") as file_contactos:
                    pass # solo creamos el archivo
                auxiliar = False
            else:
                print("Ya existe el archivo")
    else: break # Saliendo del programa    
# Procedemos a guardar todo
try:
    with open("contactos.txt","w+") as file_contactos:
        for contacto in contactos:
            linea = contacto.nombre + "," + contacto.telefono + "," + contacto.email + "\n"
            file_contactos.write(linea)
    file_contactos.close()




class Contacto:
    def _init_(self, nombre, telefono, email):
        self.nombre = nombre
        self.telefono = telefono
        self.email = email

contactos = []# Creamos la lista vacia de contactos
auxiliar = True
try:
    with open("contactos.txt","r") as file_contactos:
        for linea in file_contactos.readlines():
            informacion = linea.split(",")
            contactos.append(Contacto(informacion[0],informacion[1],informacion[2]))
    file_contactos.close()
    auxiliar = False # ya existe el archivo
except:
    print("No existe archivo previo de contactos")
    pass # si no existe el archivo no tiene que leer nada
while True :
    print("Agenda Telefonica")
    print("   1) Agregar Contacto")
    print("   2) Eliminar Contacto")
    print("   3) Mostrar Todos los Contactos")
    print("   4) Mostrar Contacto")
    print("   5) Crear Archivo")
    print("   6) Salir")
    opcion = int(input("Digite una opcion: "))
    if opcion != 6:
        if opcion == 1:
            print("Ingrese la siguiente informacion del contacto")
            nombre = input("Nombre: ")
            aux = True
            for contacto in contactos:
                if contacto.nombre == nombre:
                    aux = False
                    break
            if aux:
                telefono = input("Telefono: ")
                email = input("Email: ")
                nuevo = Contacto(nombre,telefono,email)
                contactos.append(nuevo)
                print("El contacto fue ingresado correctamente")
            else:
                print("Lo sentimos este contacto ya existe")
        elif opcion == 2:
            print("Digite el nombre del contacto a borrar")
            nombre = input("Nombre: ")
            aux1 = False
            for contacto in contactos:
                if contacto.nombre == nombre:
                    contactos.remove(contacto)
                    aux1 = True # encontrado
                    break
            if aux1:
                print("Contacto eliminado")
            else:
                print("No existe ningun contacto con este nombre")
        elif opcion == 3:
            if contactos != []:
                print("La lista de contactos")
                i = 1
                for contacto in contactos:
                    print(i,") Nombre:",contacto.nombre, "Telefono:", contacto.telefono,"Email:", contacto.email)
                    i += 1
            else:
                print("No hay contactos todavia")
        elif opcion == 4:
            print("Digite el nombre del contacto que desea ver")
            nombre = input("Nombre: ")
            for contacto in contactos:
                if contacto.nombre == nombre:
                    print(") Nombre:",contacto.nombre, "Telefono:", contacto.telefono,"Email:", contacto.email)
                    break
        elif opcion == 5:
            if auxiliar:
                print("Creando el archivo para guardar los contactos")
                with open("contactos.txt","w+") as file_contactos:
                    pass # solo creamos el archivo
                auxiliar = False
            else:
                print("Ya existe el archivo")
    else: break # Saliendo del programa    
# Procedemos a guardar todo
try:
    with open("contactos.txt","w+") as file_contactos:
        for contacto in contactos:
            linea = contacto.nombre + "," + contacto.telefono + "," + contacto.email + "\n" 
            file_contactos.write(linea)
    file_contactos.close()
    print("Saliendo y guardando")
except:
    print("Saliste sin crear el archivo")
input("Presione Enter")











