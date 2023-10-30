/*
 * tipos.h
 *
 *  Created on: 14/09/2023
 *      Author: algo2
 */

#ifndef TIPOS_H_
#define TIPOS_H_

#include "constantes.h"

enum Casilleros {
    VACIO,
    CON_ESPIA,
    CON_TESORO,
	EN_PROCESO
};

typedef struct {
	int turno;
	int tesoros;
	Casilleros matriz[MAX_FILAS][MAX_COLUMNAS];
	int en_proceso[MAX_FILAS][MAX_COLUMNAS];
}Tablero;

typedef Tablero t_jugador[CANTIDAD_DE_JUGADORES];

#endif /* TIPOS_H_ */
