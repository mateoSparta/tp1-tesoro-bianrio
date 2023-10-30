/*
 * reglas.cpp
 *
 *  Created on: 14/09/2023
 *      Author: algo2
 */

#include "interacciones.h"
#include "reglas.h"
#include "constantes.h"
#include "tipos.h"

#include <iostream>

using namespace std;

bool compararTableros(t_jugador &jugadores)
{
	bool sigueJugando = true;

	for (int i = 0; i < MAX_FILAS; i++) {
		for (int j = 0; j < MAX_COLUMNAS; j++) {
			if ((jugadores[0].matriz[i][j] == CON_ESPIA) && (jugadores[1].matriz[i][j] == CON_TESORO)) {
                cout << " - Jugador 1 encontro un teosoro" << endl;
                jugadores[0].matriz[i][j] = EN_PROCESO;
                jugadores[0].en_proceso[i][j] -= 1;
            } else if (jugadores[1].matriz[i][j] == CON_ESPIA && jugadores[0].matriz[i][j] == CON_TESORO) {
                cout << " - Jugador 2 encontro un teosoro" << endl;
                jugadores[1].matriz[i][j] = EN_PROCESO;
                jugadores[1].en_proceso[i][j] -= 1;
            } else if (jugadores[0].matriz[i][j] == CON_ESPIA && jugadores[1].matriz[i][j] == CON_ESPIA) {
            	cout << " - Se superpusieron dos espias, ambos son eliminados" << endl;
            	jugadores[0].matriz[i][j] = VACIO;
            	jugadores[1].matriz[i][j] = VACIO;
            } else if (jugadores[0].matriz[i][j] == EN_PROCESO) {
            	if (jugadores[0].en_proceso[i][j] == 0) {
            		cout << " - Jugador 1 recupero un tesoro" << endl;
            		jugadores[0].matriz[i][j] = VACIO;
            		jugadores[1].matriz[i][j] = VACIO;
            		jugadores[0].tesoros++;
            		jugadores[1].tesoros--;
            	} else {
            		jugadores[0].en_proceso[i][j] -= 1;
            	}
            } else if (jugadores[1].matriz[i][j] == EN_PROCESO) {
            	if (jugadores[1].en_proceso[i][j] == 0) {
            		cout << " - Jugador 2 recupero un tesoro" << endl;
            		jugadores[0].matriz[i][j] = VACIO;
            		jugadores[1].matriz[i][j] = VACIO;
            		jugadores[0].tesoros--;
            		jugadores[1].tesoros++;
            	} else {
            	    jugadores[1].en_proceso[i][j] -= 1;
            	}
            }
        }
    }
    if ((jugadores[0].tesoros > 0) && (jugadores[1].tesoros == 0) && (jugadores[0].turno > 0) && (jugadores[1].turno > 0)){
    	cout << endl << "El Jugador 1 es el ganador, recupero todos los tesoros" << endl;
    	sigueJugando = false;
    }else if ((jugadores[1].tesoros > 0) && (jugadores[0].tesoros == 0) && (jugadores[0].turno > 0) && (jugadores[1].turno > 0)){
    	cout << endl << "El Jugador 2 es el ganador, recupero todos los tesoros" << endl;
    	sigueJugando = false;
    }else if ((jugadores[1].tesoros == 0) && (jugadores[0].tesoros == 0) && (jugadores[0].turno > 0) && (jugadores[1].turno > 0)){
    	cout << endl << "El Jugador 1 y el Jugador 2 empataron" << endl;
    	sigueJugando = false;
    }
    return sigueJugando;
}

void inicializarTablero(t_jugador &jugadores)
{
	for (int k = 0; k < 2; k++){
		jugadores[k].turno = 0;
		jugadores[k].tesoros = 0;
		for (int i = 0; i < MAX_FILAS; i++){
			for (int j = 0 ;j < MAX_COLUMNAS; j++){
				jugadores[k].matriz[i][j] = VACIO;
				jugadores[k].en_proceso[i][j] = TURNOS_DE_RECUPERACION;
			}
		}
	}
}

void jugarTurno(t_jugador &jugadores, int numeroDeJugador)
{
	if (jugadores[numeroDeJugador].turno == 0) {
		if (numeroDeJugador == 0) {
			ingresarTesoros(jugadores[numeroDeJugador], jugadores[numeroDeJugador+1]);
		} else {
			ingresarTesoros(jugadores[numeroDeJugador], jugadores[numeroDeJugador-1]);
		}
	}
	if (jugadores[numeroDeJugador].tesoros > 0)	{
		ingresarEspia(jugadores[numeroDeJugador]);
		if (numeroDeJugador == 0) {
			moverTesoro(jugadores[numeroDeJugador], jugadores[numeroDeJugador+1]);
		} else {
			moverTesoro(jugadores[numeroDeJugador], jugadores[numeroDeJugador-1]);
		}
	}
	if (numeroDeJugador == 0) {
	   	escrbirTablero(jugadores[numeroDeJugador], numeroDeJugador+1 ,"TableroJugador1.txt");
	} else {
	    escrbirTablero(jugadores[numeroDeJugador], numeroDeJugador+1 ,"TableroJugador2.txt");
	}
}


