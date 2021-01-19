/*	  UNIVERSIDAD NACIONAL
         DE COSTA RICA

  II PROYECTO PROGRAMACION II
    JUEGO DE DAMAS ESPAÑOLAS
  INTEGRANTES:
	 LUIS VILLALOBOS GONZALEZ
*/

#include"Juego.h"
int main() {
	Juego *Damas = new Juego();
	Damas->iniciar();
	delete Damas;
	return 0;
}

/*	
						Simbologia :
				✔:Done   +: Almost done - almost idea  ... obviamente todavia medio malo
	   Falta:
	   -> [✔] + Caso Prueba (D)
		-> [✔] + Singleton Tablero(R)
		-> [✔] + Movimiento(D-R)
		-> [+] + Jugador ingrese direccion en un solo string(D)
		-> [✔] + Verificaciones al crear nodo(R-D)
		-> [✔] + Verificaciones al usar estrategia(R-D)
		-> [✔] + Verificaciones al mover la ficha del usuario(R-D)
		-> [+] + Documentacion(R) // UNICODE ¡¡¡Warning para Diego!!!
		-> [✔] + Arreglar Ganador( )
		-> [+] + UML (R)
		-> [✔] + Predefinir usuario = X, computadora = O (D)

			Criterio de evaluación Valor(PDF)
		
		10 pts -> [✔] El programa despliega correctamente el tablero (incluyendo las piezas del juego)
		5 pts  -> [✔] La interfaz del programa permite indicar cuál es la pieza a mover y su nueva posición
		10 pts -> [+] El programa verifica que las jugadas realizadas sean legales
		10 pts -> [✔] El programa tiene una opción para permitir cambiar la estrategia a utilizar					
		5 pts  -> [++] El programa verifica correctamente el fin de la partida					
		5 pts  -> [✔] El programa permite terminar en cualquier momento (finalizando la partida)
		5 pts  -> [✔] El programa permite reiniciar una partida en cualquier momento								
		5 pts  -> [✔] El programa guarda el estado de la partida						
		10 pts -> [✔] La estrategia aleatoria mueve las piezas correctamente
		10 pts -> [✔] La opción para cargar una configuración previa del tablero funciona correctamente
		15 pts -> [+] La estrategia para ganar la partida funciona correctamente
		10 pts -> [+] La estrategia adicional seleccionada está debidamente implementada (esto incluye la implementación según la documentación correspondiente)			
	Total : 65 ✔  65 / 100 contando unicamente los ✔
  */