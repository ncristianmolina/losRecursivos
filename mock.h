#ifndef MOCK_H_INCLUDED
#define MOCK_H_INCLUDED
#include "jugador.h"



#define AR_JUGADORES "jugadores.dat"

void generarContrasena(char *destino, int longitud);
void imprimirJugador(stJugador);
void generarJugadorAleatorio(stJugador *jugador, int idJugador);
void guardarJugadoresEnArchivoBinario(const char *nombreArchivo, stJugador *jugadores, int cantidad);
void leerJugadoresDesdeArchivo(const char *nombreArchivo);
void leerJugadoresDesdeArchivo(const char *nombreArchivo);
int obtenerUltimoIDPlayer();
void generarYGuardarJugadores(int cantidad);
int guardaJugadorArchivo(stJugador jugador);

#endif // MOCK_H_INCLUDED
