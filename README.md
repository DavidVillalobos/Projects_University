# SistemasOperativos
### Segundo Proyecto Sistemas Operativos
* * *
### Proyecto Distribucion de CODE-VID
El proyecto consiste en crear un modelo que simule la distribución de enfermedades con la finalidad de comprender mejor el desarrollo de estas. La simulación se visualizara en un mapa 2D donde existirán agentes, que se pueden contagiar de la enfermedad CODE-VID, estos tienen un compartimiento diferente (pero se mueven con cierto patron establecido) donde ademas se pueden colocar limitaciones fisicas dentro del mapa (Paredes).

### Pre-requisitos 📋
* Sistema Operativo Linux o un Subsistema de linux que permita el uso de la libreria pthread.h en C, como lo es Windows Subsystem Linux

### Comenzando 🚀
Una vez descargada la carpeta del proyecto, se debe descomprimir en la ubicacion deseada.
Luego inicie una terminal dentro de la carpeta /src y ejecute el siguiente codigo para iniciar la simulacion
~~~bash
make
./program #
~~~
Donde # representa la cantidad de segundos que desee que dure la simulacion, una vez finalizado este tiempo se creara un archivo .tex con la informacion recopilada de cada segundo sobre el avance de la enfermedad.

### Salida TEX
La simulación una vez terminada con los segundos ingresados generar un .tex compilable a pdf para visualizar la silmulación, cada pagina corresponde a un segundo de la simulacion, donde los puntos verdes, son agentes sanos, rojos son enfermos, azul recuperados, los agentes negros desaparecen del mapa.

### Ejecutando las pruebas ⚙️
Para configurar la simulacion debe modificar los archivos de configuración de disease.ini para la enfermedad, map.ini para el mapa y agent.ini para los agentes.

### Construido con 🛠�?
* [C]() - Lenguaje de programación utilizado
* [Threads.h]() - Libreria para el manejo de Hilos en POSIX

### Autores ✒️
* **Luis David Villalobos González**
* **Giancarlo Alvarado Sánchez**
