/*
 * interacciones.cpp
 *
 *  Created on: 14/09/2023
 *      Author: algo2
 */

#include "interacciones.h"
#include "constantes.h"
#include "tipos.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void mostrarBienvenida()
{
	cout << "Bienvenido al juego Tesoro Binario" << endl;
}

void mostrarTablero(Tablero &jugadores)
{
	for (int i = 0; i < MAX_FILAS; i++) {
		for (int j = 0; j < MAX_COLUMNAS; j++) {
			if (jugadores.matriz[i][j] == VACIO) {
				cout << "[ ]";
            } else if (jugadores.matriz[i][j] == CON_ESPIA) {
            	cout << "[E]";
            } else if (jugadores.matriz[i][j] == CON_TESORO) {
            	cout << "[T]";
            } else if (jugadores.matriz[i][j] == EN_PROCESO) {
            	cout << "[X]";
            }
        }
        cout << endl;
    }
	cout << endl;
	/* muestra el estado del tablero paralelo y los turnos de recuperacion de cada casillero
	for (int i = 0; i < MAX_FILAS; i++) {
		for (int j = 0; j < MAX_COLUMNAS; j++) {
			cout << "[" << jugadores.en_proceso[i][j] << "]";
	    }
	    cout << endl;
	}
	cout << endl;
	*/
}

void ingresarCoordenadas(int &fila, int &columna)
{
	do {
		cout << " - fila nª";
		cin >> fila;
		cout << " - columna nª";
		cin >> columna;
		cout << endl;
	} while ((fila < 1 || fila > MAX_FILAS) || (columna < 1 || columna > MAX_COLUMNAS));
}

void ingresarEspia(Tablero &jugadores)
{
	int fila, columna;

	cout << endl << "Ingrese un espia en el tablero" << endl;
	ingresarCoordenadas(fila, columna);
	while ((jugadores.matriz[fila-1][columna-1] == EN_PROCESO) || (jugadores.matriz[fila-1][columna-1] == CON_TESORO)){
		cout << "No se puede ingresar un espia en ese casillero" << endl;
		cout << "Ingrese una posicion valida" << endl;
		ingresarCoordenadas(fila, columna);
	}
	jugadores.matriz[fila-1][columna-1] = CON_ESPIA;
	mostrarTablero(jugadores);
	jugadores.turno++;
}

void moverTesoro(Tablero &jugadorActivo, Tablero &jugadorInactivo)
{
	int filaInicial, columnaInicial, filaFinal, columnaFinal;
	int quiereMover;

	if (jugadorActivo.tesoros > 0) {
		do {
			cout << "¿Desea mover algun tesoro?" << endl << "Ingrese 0 (no) o 1 (si): ";
			cin >> quiereMover;
		} while (quiereMover != 0 && quiereMover != 1);
		if (quiereMover == 1) {
			cout << "Ingrese la coordenada del tesoro que desea mover: " << endl;
			ingresarCoordenadas(filaInicial, columnaInicial);
			while (jugadorActivo.matriz[filaInicial-1][columnaInicial-1] != CON_TESORO) {
				cout << "No hay ningun tesoro en esa posicion, intente otra vez" << endl;
				ingresarCoordenadas(filaInicial, columnaInicial);
			}
			while ((jugadorActivo.matriz[filaInicial-1][columnaInicial-1] == CON_TESORO) &&
				   (jugadorInactivo.matriz[filaInicial-1][columnaInicial-1] == EN_PROCESO)) {
				cout << "El tesoro no puede moverse porque esta siendo capturado, intente otra vez" << endl;
				ingresarCoordenadas(filaInicial, columnaInicial);
			}
			cout << "Ingrese la coordenada donde desea mover el tesoro:" << endl;
			ingresarCoordenadas(filaFinal, columnaFinal);
			while ((jugadorActivo.matriz[filaFinal-1][columnaFinal-1] == CON_TESORO) ||
				   (jugadorActivo.matriz[filaFinal-1][columnaFinal-1] == EN_PROCESO) ||
				   (jugadorActivo.matriz[filaFinal-1][columnaFinal-1] == CON_ESPIA)) {
				cout << "Esta posicion no esta disponible"<< endl;
				cout << "Ingrese otra coordenada donde desea mover el tesoro:" << endl;
				ingresarCoordenadas(filaFinal, columnaFinal);
			}
			while (jugadorInactivo.matriz[filaFinal-1][columnaFinal-1] == CON_TESORO) {
				cout << "En esta posicion hay un tesoro enemigo, en el proximo turno puede colocar un espia"<< endl;
				cout << "Ingrese otra coordenada donde desea mover el tesoro:" << endl;
				ingresarCoordenadas(filaFinal, columnaFinal);
			}
			while (!((filaFinal-1 <= filaInicial) && (filaFinal-1 >= filaInicial-2) &&
				  (columnaFinal-1 <= columnaInicial) && (columnaFinal-1 >= columnaInicial-2)) &&
				  !((filaFinal-1 == -1) || (filaFinal-1 == MAX_FILAS+1)) &&
				  !((columnaFinal-1 == -1) || (columnaFinal-1 == MAX_COLUMNAS+1))) {
				cout << "la posicion excede la distancia permitida, intente otra vez" << endl;
				ingresarCoordenadas(filaFinal, columnaFinal);
			}
			jugadorActivo.matriz[filaInicial-1][columnaInicial-1] = VACIO;
			jugadorActivo.matriz[filaFinal-1][columnaFinal-1] = CON_TESORO;
			mostrarTablero(jugadorActivo);
		}
	}
}

void ingresarTesoros(Tablero &jugadorActivo, Tablero &jugadorInactivo)
{
	int fila, columna;

	for (int i = 0; i < TESOROS; i++) {
		cout << "Ingrese la coordenada donde desea colocar un tesoro:" << endl;
		ingresarCoordenadas(fila, columna);
		while ((jugadorActivo.matriz[fila-1][columna-1] == CON_TESORO) ||
			   (jugadorActivo.matriz[fila-1][columna-1] == CON_ESPIA)) {
			cout << "Esta posicion no esta disponible"<< endl;
			cout << "Ingrese otra coordenada donde desea colocar el tesoro:" << endl;
			ingresarCoordenadas(fila, columna);
		}
		while (jugadorInactivo.matriz[fila-1][columna-1] == CON_TESORO) {
			cout << "En esta posicion hay un tesoro enemigo, puede colocar un espia"<< endl;
			cout << "Ingrese otra coordenada donde desea colocar el tesoro:" << endl;
			ingresarCoordenadas(fila, columna);
		}
		jugadorActivo.matriz[fila-1][columna-1] = CON_TESORO;
		mostrarTablero(jugadorActivo);
		jugadorActivo.tesoros++;
	}
	cout << "Cantidad de tesoros: " << jugadorActivo.tesoros << endl;
}

void escrbirTablero(Tablero &jugadores, int numeroDeJugador, string ruta_tablero)
{
	ofstream salida;

	salida.open(ruta_tablero.c_str());

    for (int i = 0; i < MAX_FILAS; i++) {
        for (int j = 0; j < MAX_COLUMNAS; j++) {
            if (jugadores.matriz[i][j] == VACIO) {
            	salida << "[ ]";
            } else if (jugadores.matriz[i][j] == CON_ESPIA) {
            	salida << "[E]";
            } else if (jugadores.matriz[i][j] == CON_TESORO) {
            	salida << "[T]";
            } else if (jugadores.matriz[i][j] == EN_PROCESO) {
            	salida << "[X]";
            }
        }
        salida << endl;
    }
    salida << "Jugador: " << numeroDeJugador << endl;
    salida << "Turno: " << jugadores.turno << endl;
    salida << "Tesoros: " << jugadores.tesoros << endl << endl;
}

void mostrarInicioTurno(Tablero jugadores, int numeroDeJugador)
{
	if (numeroDeJugador == 0) {
		cout << "___________________________________________________________"<< endl;
	}
	cout << "___________________________________________________________"<< endl;
	cout << endl <<"Jugador: " << numeroDeJugador+1 << " - Turno: " << jugadores.turno+1 << endl;
}

void mostrarFinTurno(Tablero jugadores)
{
	cout << "___________________________________________________________"<< endl;
	cout << "___________________________________________________________"<< endl;
	cout << endl << "Fin del turno: " << jugadores.turno << endl;
}
