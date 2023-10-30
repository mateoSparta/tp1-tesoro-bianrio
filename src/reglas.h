/*
 * reglas.h
 *
 *  Created on: 14/09/2023
 *      Author: algo2
 */

#ifndef REGLAS_H_
#define REGLAS_H_

#include "tipos.h"

/*
 * Compara los tableros del jugador 1 y del jugador 2 para ver si hay interacciones
 * y si el juego continua
 */
bool compararTableros(t_jugador &jugadores);

/*
 * Inicializa los casilleros del tablero principal en casilleros vacios y tambien incializa
 * un tablero paralelo en el que cada casillero tiene asignado el valor de los turnos de
 * recuperacion, los cuales iran decrementando en  cada turno en el caso de que un tesoro
 * sea encontrado en la misma posicion en el tablero general
 */
void inicializarTablero(t_jugador &jugadores);

/*
 * Determina el trascurso del turno segun las condiciones de cada jugador
 */
void jugarTurno(t_jugador &jugadores, int numeroDeJugador);

#endif /* REGLAS_H_ */
