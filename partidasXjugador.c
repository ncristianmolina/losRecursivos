#include <stdio.h>
#include <stdlib.h>
#include "inicio-sesion.h"
#include "registro.h"
#include "tateti.h"
#include "jugador.h"
#include "mock.h"
#include "partidas.h"
#include "partidasXjugador.h"
#include <locale.h>

#define AR_PARTIDASXJUGADOR "partidasxjugador.dat"

void imprimirPartidasporJugador(stPartidaXJugador pxj)
  {
        printf("ID Partida Jugador: %d\n", pxj.idPartidaJugador);
        printf("ID Partida: %d\n", pxj.idPartida);
        printf("ID Jugador: %d\n", pxj.idJugador);
        printf("Resultado: %d\n", pxj.resultado);
        printf("Puntos Jugador: %d\n", pxj.puntosJugador);
        printf("----------------------------------------\n");
   }




stPartidaXJugador generarPartidaXJugador(int idPartidaJugador, int idPartida, int idJugador) {
    stPartidaXJugador pxj;
    pxj.idPartidaJugador = idPartidaJugador;
    pxj.idPartida = idPartida;
    pxj.idJugador = idJugador;
    pxj.resultado = rand() % 3; // 0, 1 o 2

    if (pxj.resultado == 1)
    pxj.puntosJugador = 3;     // victoria
    else if (pxj.resultado == 2)
    pxj.puntosJugador = 1;     // empate
    else
    pxj.puntosJugador = 0;     // derrota

    return pxj;
}




 void guardarPartidasxJugadorEnArchivo(const char *nombreArchivo, stPartidaXJugador *pxj, int cantidad) {
    FILE *archi = fopen(nombreArchivo, "ab");
    if (archi) {
        fwrite(pxj, sizeof(stPartidaXJugador), cantidad, archi);
        fclose(archi);
        printf("Se guardaron %d partidas por jugador en el archivo binario.\n", cantidad);
    }


}


void leerPartidasPorJugadorDesdeArchivo(const char *nombreArchivo) {
    FILE *archi = fopen(nombreArchivo, "rb");
    if (archi) {
        stPartidaXJugador pxj;
        printf("\n--- Partidas por jugador guardadas ---\n");
        while (fread(&pxj, sizeof(stPartidaXJugador), 1, archi) == 1) {
            imprimirPartidasporJugador(pxj);
        }
        fclose(archi);
    }
}


void generarYGuardarPartidasXJugador(const char *archivo, stJugador *jugadores, int cantJugadores, stPartida *partidas, int cantPartidas) {
    stPartidaXJugador registros[CANT_PARTIDAS_X_JUGADOR];

    for (int i = 0; i < CANT_PARTIDAS_X_JUGADOR; i++) {
        int idJugador = jugadores[rand() % cantJugadores].idJugador;
        int idPartida = partidas[rand() % cantPartidas].idPartida;

        registros[i] = generarPartidaXJugador(i + 1, idPartida, idJugador);
    }

    guardarPartidasxJugadorEnArchivo(archivo, registros, CANT_PARTIDAS_X_JUGADOR);
}
