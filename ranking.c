#include <stdio.h>
#include <string.h>
#include "ranking.h"
#include "partidasXjugador.h"
#define ARCHIVO_JUGADORES "jugadores.dat"
#define AR_PARTIDASXJUGADOR "partidasxjugador.dat"

/* Hecho por Cristian. Muestra estadísticas del jugador. */
void mostrarEstadisticasJugador(int idJugador) {
    FILE *archiPartidas = fopen(AR_PARTIDASXJUGADOR, "rb");
    if (!archiPartidas) {
        printf("Error al abrir el archivo %s.\n", AR_PARTIDASXJUGADOR);
        return;
    }

    int totalPartidas = 0, victorias = 0, empates = 0, derrotas = 0;
    stPartidaXJugador pxj;

    while (fread(&pxj, sizeof(stPartidaXJugador), 1, archiPartidas) == 1) {
        if (pxj.idJugador == idJugador) {
            totalPartidas++;
            if (pxj.resultado == 1) victorias++;
            else if (pxj.resultado == 2) empates++;
            else derrotas++;
        }
    }
    fclose(archiPartidas);

    float porcentajeVictorias = (totalPartidas > 0) ? (victorias * 100.0 / totalPartidas) : 0;
    float porcentajeEmpates = (totalPartidas > 0) ? (empates * 100.0 / totalPartidas) : 0;
    float porcentajeDerrotas = (totalPartidas > 0) ? (derrotas * 100.0 / totalPartidas) : 0;

    printf("\n=== Estadísticas del Jugador (ID: %d) ===\n", idJugador);
    printf("Total Partidas Jugadas: %d\n", totalPartidas);
    printf("Victorias: %d (%.2f%%)\n", victorias, porcentajeVictorias);
    printf("Empates: %d (%.2f%%)\n", empates, porcentajeEmpates);
    printf("Derrotas: %d (%.2f%%)\n", derrotas, porcentajeDerrotas);
}

/* Hecho por Cristian. Muestra ranking jugadores puntos. */
void mostrarRankingJugadores() {
    FILE *archi = fopen(ARCHIVO_JUGADORES, "rb");
    if (!archi) {
        printf("Error al abrir el archivo %s.\n", ARCHIVO_JUGADORES);
        return;
    }

    stJugador jugadores[100];
    int count = 0;

    // Leer todos los jugadores
    while (fread(&jugadores[count], sizeof(stJugador), 1, archi) == 1 && count < 100) {
        if (!jugadores[count].eliminado) {
            count++;
        }
    }
    fclose(archi);

    // Ordenar por puntos (burbujeo descendente)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (jugadores[j].ptsTotales < jugadores[j + 1].ptsTotales) {
                stJugador temp = jugadores[j];
                jugadores[j] = jugadores[j + 1];
                jugadores[j + 1] = temp;
            }
        }
    }

    // Mostrar ranking
    printf("\n=== Ranking de Jugadores ===\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s %s (ID: %d, Username: %s) - Puntos: %d\n",
               i + 1, jugadores[i].nombre, jugadores[i].apellido, jugadores[i].idJugador, jugadores[i].username, jugadores[i].ptsTotales);
    }
    if (count == 0) {
        printf("No hay jugadores registrados.\n");
    }
}
