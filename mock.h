#ifndef MOCK_H_INCLUDED
#define MOCK_H_INCLUDED
#include "jugador.h"

#define AR_JUGADORES "jugadores.dat"
#define SIZE 3

int casillaRandom(char tablero[SIZE][SIZE], char jugador);
int dificultadDificil(char tablero[SIZE][SIZE], char jugador);
void generarContrasena(char *destino, int longitud);
void imprimirJugador(stJugador);
void generarJugadorAleatorio(stJugador *jugador, int idJugador);
void guardarJugadoresEnArchivoBinario(const char *nombreArchivo, stJugador *jugadores, int cantidad);
void leerJugadoresDesdeArchivo(const char *nombreArchivo);
int obtenerUltimoIDPlayer();
void generarYGuardarJugadores(int cantidad);
int guardaJugadorArchivo(stJugador jugador);
void guardarJugadoresEnArchivo(const char *nombreArchivo, stJugador *jugadores, int cantidad); // esta es la de tu amiga

#endif // MOCK_H_INCLUDED
