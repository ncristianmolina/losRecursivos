#ifndef MOCK_H_INCLUDED
#define MOCK_H_INCLUDED
#include "jugador.h"



#define NUM_JUGADORES_ALEATORIOS 2000
#define NUM_JUGADORES_CARGADOS 0
#define TOTAL_JUGADORES (NUM_JUGADORES_CARGADOS + NUM_JUGADORES_ALEATORIOS)
#define jugadoresPrecargados[NUM_JUGADORES_PRECARGADOS];

#define AR_JUGADORES "jugadores.dat"

void generarContrasena(char *destino, int longitud);
void imprimirJugador(stJugador);
void generarJugadorAleatorio(stJugador *jugador, int idJugador);
void guardarJugadoresEnArchivoBinario(const char *nombreArchivo, stJugador *jugadores, int cantidad);
void leerJugadoresDesdeArchivo(const char *nombreArchivo);
void leerJugadoresDesdeArchivo(const char *nombreArchivo);



#endif // MOCK_H_INCLUDED
