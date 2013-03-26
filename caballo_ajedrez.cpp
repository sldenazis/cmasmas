/*
 *       Autor: Santiago López Denazis
 *        Mail: sldenazis@gmail.com
 *       Fecha: 2013/03/25
 * Descripcion: Encuentra por fuerza bruta un camino para recorrer todas las casillas del tablero con un caballo.
 *     Version: 0.1
 *    Licencia: GPLv3 o superior.
 */

#include <iostream>
using namespace std;

bool termineRecorrido( bool tablero[8][8] ){
	// Si todos los escaques estan en true, devuelvo true

	bool termine = false;
	short escaques_visitados = 0;

	for ( short fila = 0; fila < 8; fila++ ){
		for ( short columna = 0; columna < 8; columna++ ){
			if ( tablero[fila][columna] ) { escaques_visitados++; }
		}
	}

	if ( escaques_visitados == 64 ) { termine = true; }

	return termine;
}

bool validaMovimiento( bool tablero[8][8], short fila, short columna ){
	// Devuelve true si el movimiento es valido
	
	bool puedo_mover = true;

	if ( fila < 8 && fila >= 0 && columna < 8 && columna >= 0 ){
		if ( tablero[fila][columna] ) { puedo_mover = false; }
	} else {
		puedo_mover = false;
	}

	return puedo_mover;
}

int mueve( bool tablero[8][8], short fila, short columna, int nivel ){

	int solucionado = 1; // no encontre la solucion si no esta en 0
	
	tablero[fila][columna] = true;

	cout << "Fila: " << fila << ", columna: " << columna << endl;
	nivel++;

	if ( termineRecorrido(tablero) ){
		cout << "Finalizamos en el nivel " << nivel << "." << endl;
		return 0;
	} else {
		if ( validaMovimiento( tablero, fila+1, columna+2 ) ){
			solucionado = mueve( tablero, fila+1, columna+2, nivel );
		}
		if ( solucionado != 0 ){
			if ( validaMovimiento( tablero, fila+2, columna+1 ) ){
				solucionado = mueve( tablero, fila+2, columna+1, nivel );
			}
		}
		if ( solucionado != 0 ){
			if ( validaMovimiento( tablero, fila+2, columna-1 ) ){
				solucionado = mueve( tablero, fila+2, columna-1, nivel );
			}
		}
		if ( solucionado != 0 ){
			if ( validaMovimiento( tablero, fila+1, columna-2 ) ){
				solucionado = mueve( tablero, fila+1, columna-2, nivel );
			}
		}
		if ( solucionado != 0 ){
			if ( validaMovimiento( tablero, fila-1, columna-2 ) ){
				solucionado = mueve( tablero, fila-1, columna-2, nivel );
			}
		}
		if ( solucionado != 0 ){
			if ( validaMovimiento( tablero, fila-2, columna-1 ) ){
				solucionado = mueve( tablero, fila-2, columna-1, nivel );
			}
		}
		if ( solucionado != 0 ){
			if ( validaMovimiento( tablero, fila-2, columna+1 ) ){
				solucionado = mueve( tablero, fila-2, columna+1, nivel );
			}
		}
		if ( solucionado != 0 ){
			if ( validaMovimiento( tablero, fila-1, columna+2 ) ){
				solucionado = mueve( tablero, fila-1, columna+2, nivel );
			}
		}
	}

	return 1;
}

int main(){
	bool tablero_inicial[8][8];
	// Inicializo el tablero en false
	for ( short fila = 0; fila < 8; fila++ ){
		for ( short columna = 0; columna < 8; columna++){
			tablero_inicial[fila][columna] = false;
		}
	}

	mueve( tablero_inicial, 0, 0 );

	return 0;
}
