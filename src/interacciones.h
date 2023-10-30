/*
 * interacciones.h
 *
 *  Created on: 14/09/2023
 *      Author: algo2
 */

#ifndef INTERACCIONES_H_
#define INTERACCIONES_H_

#include "tipos.h"

#include <string>

using namespace std;

/*
 * Muestra el tablero en consola
 */
void mostrarTablero(Tablero &jugadores);

/*
 * Pide al usuario que ingrese una numero de fila y un numero de columna
 */
void ingresarCoordenadas();

/*
 * Coloca un espia en el casillero ingresado
 */
void ingresarEspia(Tablero &jugadores);

/*
 * Ofrece al ususario la opcion de mover casillero algun tesoro
 */
void moverTesoro(Tablero &jugadorActivo, Tablero &jugadorInactivo);

/*
 * Coloca un tesoro en el casillero ingresado
 */
void ingresarTesoros(Tablero &jugadorActivo, Tablero &jugadorInactivo);

/*
 * Muestra un mensaje de bienvenida
 */
void mostrarBienvenida();

/*
 * Escribe el tablero actual en un archivo.txt
 */
void escrbirTablero(Tablero &jugadores, int numeroDeJugador, string ruta_tablero);

/*
 * Muestra el mensaje de inicio de turno
 */
void mostrarInicioTurno(Tablero jugadores, int numeroDeJugador);

/*
 * Muestra el mensaje de final de turno
 */
void mostrarFinTurno(Tablero jugadores);

#endif /* INTERACCIONES_H_ */
