#ifndef PARTIDASXJUGADOR_H_INCLUDED
#define PARTIDASXJUGADOR_H_INCLUDED

typedef struct {
    int idPartidaJugador;
    int idPartida;
    int idJugador;
    int resultado;       // 0 = pierde, 1 = gana, 2 = empate
    int puntosJugador;   // 3 = gana, 1 =  empate y 0 = derrota
} stPartidaXJugador;

#define CANT_PARTIDAS_X_JUGADOR 100

void imprimirPartidasporJugador(stPartidaXJugador pxj);
stPartidaXJugador generarPartidaXJugador(int idPartidaJugador, int idPartida, int idJugador);
void guardarPartidasxJugadorEnArchivo(const char *nombreArchivo, stPartidaXJugador *pxj, int cantidad);
void leerPartidasDesdeArchivo(const char *nombreArchivo);
void generarYGuardarPartidasXJugador(const char *archivo, stJugador *jugadores, int cantJugadores, stPartida *partidas, int cantPartidas);

#endif // PARTIDASXJUGADOR_H_INCLUDED
