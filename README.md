# SistemasOperativos
### Segundo Proyecto Sistemas Operativos
* * *
### Proyecto Distribucion de CODE-VID
El proyecto consiste en desarrollar un modelo sobre un mapa que muestre como ciertos agentes con compartimiento diferente( pero que se muevan con cierto patron), se pueden ir contagiando de una enfermedad, a esta la vamos a llamar Code-vid

### Pre-requisitos 📋
* Sistema Operativo Linux o un Subsistema de linux que permita el uso de la libreria pthread.h en C, como lo es Windows Subsystem Linux

### Comenzando 🚀
Una vez descargada la carpeta del proyecto, se debe descomprimir en la ubicacion deseada.
Luego inicie una terminal dentro de la carpeta /src y ejecute el siguiente codigo para iniciar la simulacion
~~~bash
./program s
~~~
Donde s representa los segundos que durará la simulacion, una vez finalizado se creara un archivo .tex con la informacion recopilada de cada segundo sobre el avance del CODE-VID
### Ejecutando las pruebas ⚙️
Para configurar la simulacion debe modificar los archivos de configuracion de disease.ini, map.ini y agent.ini.
### Construido con 🛠️
* [C]() - Lenguaje de programación utilizado
* [Threads.h]() - Libreria para el manejo de Hilos en POSIX
### Autores ✒️
* **Luis David Villalobos González**
* **Giancarlo Alvarado Sánchez**
