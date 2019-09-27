import tkinter
tkinter.Tcl().eval('info patchlevel')
print("k")
input("")
"""
	Curse: Principios de Programacion
	Author: Dylan Gonzalez
	Date: 25/06/2019


#Ejercicio 1
file = open('data1.txt','w+')
file.write('José 28\n'
           'Sebastian 20\n'
           'Daniel 23\n'
           'Raquel 19\n'
           'Gabriela 26\n'
           'Liliana 34\n'
           'Joyce 28\n'
           'Beatriz 25\n'
           'Luis 20\n'
           'María 19\n'
           'Gabriel 25\n'
           'Dione 18\n'
           'Jen 25\n'
           'Victoria 25\n'
           'Priscila 35\n'
           'Fabio 28\n'
           'Karla 22\n'
           'Edwin 37\n'
           'Alejandro 20\n'
           'Xinia 56\n'
           'Eduardo 57\n'
           'Alana 25\n'
           'Darel 29\n'
           'Oscar 34\n'
           'Pablo 36\n'
           'Steven 32\n'
           'Gerald 23\n'
           'John 32\n'
           'Brandon 31\n'
           'Margeary 21\n'
           'Leiva 20\n'
           'Samantha 22\n'
           'Lily 30\n'
           'Gloriana 20\n'
           'Italia 23\n'
           'Ivan 30\n'
           'Katherine 67\n'
           'Daniel 32\n'
           'Jacob 21\n'
           'Valery 22\n'
           'Joselin 54\n'
           'Eva 32\n'
           'Norma 53\n'
           'Paula 29\n'
           'Lucia 19\n'
           'Alicia 21\n'
           'Sebastian 20\n'
           'Max 8\n'
           'Juan 21\n'
           'Yisus 2018\n')
file = open('data1.txt','r')
content = file.read()
copy = open('data2.txt','w+')
copy.write(content)
file.close()
copy.close()

#Ejercicio 2
file = open("data1.txt", "r")
data = file.readlines()
names = []
ages = []
print("   Lista de personas")
print(" Nombre          Edad")
for person in data:
    index = person.find(" ")
    ages.append(int(person[index:len(person)-1]))
    names.append(person[:index])
    print(names[len(names)-1].ljust(17),ages[len(ages)-1])
file.close()
senior = max(ages)
young = min(ages)
print("\n  Informacion Solicitada")
print("La persona mas vieja es :", names[ages.index(senior)], " con ", senior, " años")
print("La persona mas joven es:", names[ages.index(young)], " con ", young, " años")
print("El promedio de edad es de:", sum(ages)/len(ages), "años.\n")

#Ejercicio 3
import csv
with open ("servicios_publicos.csv", "r") as file_empleado:
    reader = csv.reader(file_empleado, delimiter = ";")
    data = {}
    for row in reader:
        if row[2] not in data:
            data.setdefault(row[2],int(row[4]))
        else:
            data[row[2]] += int(row[4])
    print("  Servicios y Consumo Totalizado ")
    for servicio,consumo in data.items():
        print(servicio.ljust(17), consumo)
file_empleado.close()
"""
a = [1,2,3,3,3]
print(a.count(8))
with open ("productos.txt", "r") as productos:
    for line in productos.readlines():
        print(line[:line.find(",")])
        print(line[line.find(",")+1:])
productos.close()




