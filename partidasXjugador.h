#ifndef PARTIDASXJUGADOR_H_INCLUDED
#define PARTIDASXJUGADOR_H_INCLUDED

#include "jugador.h"
#include "partidas.h"

#define CANT_PARTIDAS_X_JUGADOR 100
#define AR_PARTIDASXJUGADOR "partidasxjugador.dat"

typedef struct {
    int idPartidaJugador;
    int idPartida;
    int idJugador;
    int resultado;       // 0 = pierde, 1 = gana, 2 = empate
    int puntosJugador;   // 3 = gana, 1 = empate, 0 = derrota
} stPartidaXJugador;

void imprimirPartidasporJugador(stPartidaXJugador pxj);
stPartidaXJugador generarPartidaXJugador(int idPartidaJugador, int idPartida, int idJugador, int resultado);
void guardarPartidasxJugadorEnArchivo(const char *nombreArchivo, stPartidaXJugador *pxj, int cantidad);
void leerPartidasPorJugadorDesdeArchivo(const char *nombreArchivo);
void generarYGuardarPartidasXJugador(const char *archivo, stJugador *jugadores, int cantJugadores, stPartida *partidas, int cantPartidas);
void generarPartidaXJugadorParaLogueado(stJugador jugador, int idPartida);
void generarPartidaXJugadorParaVersus(stJugador jugador1, stJugador jugador2, int idPartida, int resultadoPartida);
void mostrarHistorialPartidasJugador(int idJugador);
void mostrarRankingJugadores(void);
int obtenerUltimoIdPartidaXJugador(void);

#endif // PARTIDASXJUGADOR_H_INCLUDED
