# SistemasOperativos
### Primer Proyecto Sistemas Operativos
* * *
### Proyecto Puente
El proyecto consiste en administrar un puente que solo tiene el ancho de un autotomovil, lo cual hace que en un momento dado solo pueda haber automoviles en uno de los dos sentidos, la idea es que dado esos recursos se logre administras de la mejor manera el puente permitiendo que exista una maxima utilizacion con la minima cantidad de automoviles esperando ademas de una asignacion justa del puente priorizando, se implemento con el lenguaje de programacion C y la libreria "pthread.h".
La simulacion contiene 3 modalidades:
___1) FIFO:___ Donde los automoviles seran procesados conforme vayan llegando, mientras su sector este cruzando o el puente se encuentre vacio, en otro caso debera esperar a que los automoviles provenientes del otro sector terminen de cruzar.
___2) SEMAPHORES:___ Los automoviles siguen una señal de semaforo para poder pasar y que esta activa una cierta cantidad de tiempo que es independiente en cada sector.
___3) OFFICERS:___ En esta solo es permitido que pase una cierta cantidad de automoviles por medio de turnos que son administrados por un oficial de transito.
* * *
### Comenzando 🚀

Una vez descargada la carpeta del proyecto descomprimala en la ubicacion deseada.
Abra una terminal dentro de la carpeta y ejecute 
~~~bash
./start
~~~
O para obtener mas informacion ejecute
~~~bash
 ./start help
~~~
### Pre-requisitos 📋
* Sistema Operativo Linux o un Subsistema de linux para el uso de pthread.h en C
### Ejecutando las pruebas ⚙️
Para realizar pruebas una vez descargado el programa, modifica el archivo de configuracion desde tests/config.ini o crea uno nuevo siguiendo el siguiente formato
~~~bash
[Seccion]
Variable = Valor # Comentario
~~~
La simulacion necesita de las siguientes secciones para configurar todas las variables de otra forma la simulacion no se ejecuta y emite un mensaje de error.

> __Modality__
  Un ID (id = 2 )de la simulacion este va de 1 a 3, ademas una cantidad de carros que sera compartida por los sectores.  
> __Bridge__
     Se necesita el tamaño (length = 5), que representa el numero de bloques por los que los automoviles deberan pasar para cruzar el puente.
> __East y West__
    Cada sector debera contener
    Un promedio de segundos de la llegada de vehiculos al cruze del puente
    entre mas grande sea el numero mas sera el tiempo de llegada entre los vehiculos
    average_cars = 3 
    Un numero de carros permitos por el oficial si la modalidad 3 es escogida k_number_cars = 5 
    Tiempo en segundos en que la luz del semaforo se encuentra en verde 
    time_green_light = 10 
    Un rango para las velocidades de los automoviles, ingresando un Maximo y un Minimo
    maximum_speed_cars = 2
    minimum_speed_cars = 1
    Finalmente la probabilidad de la presencialidad de ambulancias, esta va de 1 a 10 cada numero representa su porcentaje equivalente 10% a 100%, ejemplo 
    ambulance_probability = 3 
    Es decir un 30% de los automoviles que pasen seran ambulancias aproximadamente
### Construido con 🛠️
* [C]() - Lenguaje de programación utilizado
* [Threads.h]() - Libreria para el manejo de Hilos en POSIX
### Autores ✒️
* **Luis David Villalobos González**
* **Giancarlo Alvarado**