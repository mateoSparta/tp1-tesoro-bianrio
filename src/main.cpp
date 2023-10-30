/*
 * main.cpp
 *
 *  Created on: 10/09/2023
 *      Author: algo2
 */

#include "interacciones.h"
#include "reglas.h"
#include "constantes.h"
#include "tipos.h"

int main()
{
	bool sigueJugando = true;
	t_jugador jugadores;

	mostrarBienvenida();
	inicializarTablero(jugadores);
	while (sigueJugando) {
		for (int numeroDeJugador = 0; numeroDeJugador < 2; numeroDeJugador++) {
			mostrarInicioTurno(jugadores[numeroDeJugador], numeroDeJugador);
	        mostrarTablero(jugadores[numeroDeJugador]);
	        jugarTurno(jugadores, numeroDeJugador);
		}
		mostrarFinTurno(jugadores[1]);
		if (jugadores[0].turno > 0 && jugadores[1].turno > 0) {
			sigueJugando = compararTableros(jugadores);
		}
	}
	return 0;
}
