# SistemasOperativos
### Primer Proyecto Sistemas Operativos
* * *
### Proyecto Puente
El siguiente proyecto consiste en administrar un puente por el cual cruzan vehiculos entre el sector este y oeste, dado que el puente tiene el ancho de un autotomovil hace que en un momento dado solo puedan existir automoviles en uno de los dos sentidos, la idea es que dado ese recurso se logre administrar de la mejor, permitiendo que exista una maxima utilización del mismo con la minima cantidad de automoviles esperando ademas de una asignacion justa del puente priorizando las ambulancias, se implemento con el lenguaje de programacion C y la libreria "pthread.h", la administracion es manejada por 3 modalidades distintas:
* * *
___1) FIFO:___ Donde los automoviles seran procesados conforme vayan llegando, mientras su sector este cruzando o el puente se encuentre vacio, en otro caso deberan esperar que los automoviles provenientes del otro sector terminen de cruzar, asi el puente estará vacio.
* * *
___2) SEMAPHORES:___ Los automoviles siguen una señal de semaforo para poder cruzar y que está activa una cierta cantidad de segundos que es independiente en cada sector.
* * *
___3) OFFICERS:___ En esta un oficial permite que pasen una cierta cantidad de automoviles por turnos, esta cantidad tambien es independiente de cada sector.
* * *
En cualquiera de ellas existe la prioridad de paso para las ambulancias, siempre y cuando estas puedan pasar, es decir evitando que se provoquen dead locks (Colisión de automoviles al cruzar el puente).
### Pre-requisitos 📋
* Sistema Operativo Linux o un Subsistema de linux que permita el uso de la libreria pthread.h en C
### Comenzando 🚀
Una vez descargada la carpeta del proyecto, se debe descomprimir en la ubicacion deseada.
Luego inicie una terminal dentro de la carpeta /src y ejecute el siguiente codigo para iniciar la simulacion
~~~bash
./start
~~~
Esta predeterminado que la simulacion toma la configuracion presente en el archivo test/config.ini para obtener mas información acerca de como ejecutarlo con otros archivos o modalidades puede escribir
~~~bash
 ./start help
~~~
### Ejecutando las pruebas ⚙️
Para realizar pruebas puede modificar el archivo de configuracion presente en la carpeta test/config.ini o crear uno nuevo basandose en ese archivo con el siguiente formato:
~~~bash
[Seccion]
Variable = Valor # Comentario
~~~
La simulacion necesita de las siguientes secciones para configurar todas las variables de otra forma la simulacion no se ejecuta y emite un mensaje de error.
* * *
> __Modality__:
  Un ID (id = 2 ) de la simulacion este va de 1 a 3, ademas una cantidad de carros que sera compartida por los sectores.
* * *
> __Bridge__:
     Se necesita el tamaño (length = 5), que representa el numero de bloques por los que los automoviles deberan pasar para cruzar el puente.
* * *
> __East y West__:
    Cada sector debera contener un promedio de segundos de la llegada de vehiculos al cruze del puente entre mas grande sea el numero
				mas sera el tiempo de llegada entre los vehiculos ( average_cars = 3 ) Un numero de carros permitos por el oficial si la modalidad 3
				es elegida ( k_number_cars = 5 ) 
    Tiempo en segundos en que la luz del semaforo se encuentra en verde ( time_green_light = 10 ) 
    Un rango para las velocidades de los automoviles, ingresando un Maximo y un Minimo
    ( maximum_speed_cars = 2 )
    ( minimum_speed_cars = 1 )
    Finalmente la probabilidad de la presencialidad de ambulancias, esta va de 1 a 10, cada digito representa su porcentaje equivalente
				de 10% a 100% por ejemplo( ambulance_probability = 3 ) determina que un 30% de los automoviles que pasen seran ambulancias
				en toda la ejecucion de la simulacion para ese sector aproximadamente.

### Construido con 🛠️
* [C]() - Lenguaje de programación utilizado
* [Threads.h]() - Libreria para el manejo de Hilos en POSIX

### Autores ✒️
* **Luis David Villalobos González**
* **Giancarlo Alvarado Sánchez**


