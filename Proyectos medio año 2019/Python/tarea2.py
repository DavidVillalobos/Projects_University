#Creamos la clase producto
class Producto: # La clase producto unicamente tiene dos atributos
    def __init__(self, nombre, precio):# constructor
        self.nombre = nombre# definicion de variables
        self.precio = precio
        
#Vamos a ingresar el inventario
inventario = {}# inicializams le diccionario vacio
with open ("productos.txt", "r") as archivo_productos:# abrimos el archivo
    i = 1# este iterador lo utilizamos para generar los codigos autonumericos
    for line in archivo_productos.readlines():# por cada linea del archivo
        #ingresamos el producto al archivo para ello sabemos que en el archivo esta limitado
        # por una coma es decir     Arroz,2500   con la funcion find encontramos la limitacion y separamos el texto        
        # leemos las variables del archivo
        nombre = line[:line.find(",")] # Aca se aplica slice desde el inicio hasta la coma, es decir el nombre
        precio = int(line[line.find(",")+1:])# slice del la coma + 1 hasta el final es decir el precio
        nuevo = Producto(nombre,precio) # creamos el producto
        inventario.setdefault(i,nuevo)# e insertamos sl inventario(diccionario) con la 
        #funcion setdefault que es el equivalente  a append en listas
        i += 1
archivo_productos.close()

import os# ahorita entiende esto. . . 
#Tomamos un carrito e ingresamos los productos
carrito = []
while(True):# este while(True) es muy comun en programacion para ejecutar acciones ciclicas
# la unica forma de salir del while es con un break
    print("SUPER TICO\n1)Arroz\n2)Frijoles\n3)Aceite\n4)Leche\n5)Huevos\n6)Pescado\n7)Res\n8)Agua Bendita\n9)Pagar\n")
    print("Carrito [",end="")
    for product in carrito:
        print(product.nombre,"",end="")
    print("]")
    i = int(input("Elige una opcion: "))
    if i != 9:# si la opcion no es pagar
        n = int(input("Cuantas unidades desea:"))
        for e in range(n):
            # hacemos un control de expeciones, si falla es por que el codigo no existe
            # es un sistema donde se realiza una prueba(try) de un codigo
            # si este genera un error se detiene y realiza la ejecucion respaldo o excepcion(except)
            try:
                carrito.append(inventario[i])# da error si el i(llave del diccionario) que es enviado no existe
            except:
                print("Este codigo no existe")
                break# break es una funcion que rompe el ciclo del for sin que este haya terminado
    else: break# si es pagar rompa el ciclo
    # estas funciones funcionan con el modulo os del sistema por ello se importa en la linea 23
    os.system("pause")# presione cualquier tecla para continuar...
    os.system ("cls") # clear scream que es limpiar pantalla para que no se acomule la informacion

#Pasamos a la caja a pagar
# creamos una variable factura vacia que va irse concatenando con los productos 
total = 0# variable de suma total
i = 1 # variable auxiliar del numero de linea de la factura
print("Super tico")
factura = ""
for product in carrito:# por cada producto en el carrito
    #concatenamos para ir añadiendo la factura
    factura += str(i) + " " + product.nombre + " " + str(product.precio) + "\n"
    total += product.precio # vamos sumando para calcular el total
    i += 1
factura += "SubTotal: " + str(total) + "\n"
factura += "Total: " + str(round(total*1.13)) 
print(factura)# imprimimos la factura y la guardamos en un archivo
with open ("ventas.txt", "w+") as archivo_ventas:
    archivo_ventas.write(factura)
archivo_ventas.close()
print("Presione ctrl z")
# Programa terminado