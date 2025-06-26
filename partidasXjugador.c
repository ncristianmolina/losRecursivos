#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "jugador.h"
#include "inicio-sesion.h"
#include "partidas.h"
#include "partidasXjugador.h"

#define AR_PARTIDASXJUGADOR "partidasxjugador.dat"
#define ARCHIVO_JUGADORES "jugadores.dat"

/** Hecha por Luciana. Muestra partida por jugador **/
void imprimirPartidasporJugador(stPartidaXJugador pxj) {
    printf("ID Partida Jugador: %d\n", pxj.idPartidaJugador);
    printf("ID Partida: %d\n", pxj.idPartida);
    printf("ID Jugador: %d\n", pxj.idJugador);
    printf("Resultado: %d (0=derrota, 1=victoria, 2=empate)\n", pxj.resultado);
    printf("Puntos Jugador: %d\n", pxj.puntosJugador);
    printf("----------------------------------------\n");
}

/** Hecha por Luciana. Genera partida por jugador **/
stPartidaXJugador generarPartidaXJugador(int idPartidaJugador, int idPartida, int idJugador, int resultado) {
    stPartidaXJugador pxj;
    pxj.idPartidaJugador = idPartidaJugador;
    pxj.idPartida = idPartida;
    pxj.idJugador = idJugador;
    pxj.resultado = resultado;

    if (pxj.resultado == 1)
        pxj.puntosJugador = 3;     // victoria
    else if (pxj.resultado == 2)
        pxj.puntosJugador = 1;     // empate
    else
        pxj.puntosJugador = 0;     // derrota

    return pxj;
}

/** Hecha por Luciana. Guarda partidas por jugador en archivo **/
void guardarPartidasxJugadorEnArchivo(const char *nombreArchivo, stPartidaXJugador *pxj, int cantidad) {
    FILE *archi = fopen(nombreArchivo, "ab");
    if (archi) {
        fwrite(pxj, sizeof(stPartidaXJugador), cantidad, archi);
        fclose(archi);
    }
    printf("Se guardaron %d partidas por jugador en el archivo.\n", cantidad);
}

/** Hecha por Luciana. Muestra partidas por jugador almacenadas en el archivo **/
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

int obtenerUltimoIdPartidaXJugador() {
    FILE *archi = fopen(AR_PARTIDASXJUGADOR, "rb");
    int ultimoID = 0;
    stPartidaXJugador aux;

    if (archi) {
        fseek(archi, 0, SEEK_END);
        long long totalRegistros = ftell(archi) / sizeof(stPartidaXJugador);
        if (totalRegistros > 0) {
            fseek(archi, -1 * (long long)sizeof(stPartidaXJugador), SEEK_END);
            fread(&aux, sizeof(stPartidaXJugador), 1, archi);
            ultimoID = aux.idPartidaJugador;
        }
        fclose(archi);
    }
    return ultimoID;
}

void generarYGuardarPartidasXJugador(const char *archivo, stJugador *jugadores, int cantJugadores, stPartida *partidas, int cantPartidas) {
    stPartidaXJugador registros[CANT_PARTIDAS_X_JUGADOR];
    int ultimoID = obtenerUltimoIdPartidaXJugador();

    for (int i = 0; i < CANT_PARTIDAS_X_JUGADOR; i++) {
        int idJugador = jugadores[rand() % cantJugadores].idJugador;
        int idPartida = partidas[rand() % cantPartidas].idPartida;
        int resultado = rand() % 3; // 0=derrota, 1=victoria, 2=empate

        registros[i] = generarPartidaXJugador(ultimoID + i + 1, idPartida, idJugador, resultado);

        // Actualizar puntos del jugador
        stJugador jugador;
        FILE *jugadoresFile = fopen(ARCHIVO_JUGADORES, "rb+");
        if (jugadoresFile) {
            while (fread(&jugador, sizeof(stJugador), 1, jugadoresFile) == 1) {
                if (jugador.idJugador == idJugador && !jugador.eliminado) {
                    jugador.ptsTotales += registros[i].puntosJugador;
                    fseek(jugadoresFile, -1 * (long long)sizeof(stJugador), SEEK_CUR);
                    fwrite(&jugador, sizeof(stJugador), 1, jugadoresFile);
                }
            }
            fclose(jugadoresFile);
        }
    }

    guardarPartidasxJugadorEnArchivo(archivo, registros, CANT_PARTIDAS_X_JUGADOR);
}

void generarPartidaXJugadorParaLogueado(stJugador jugador, int idPartida) {
    FILE *archi = fopen(AR_PARTIDASXJUGADOR, "rb");
    int ultimoID = 0;
    stPartidaXJugador aux;

    // Obtener el último ID de partida por jugador
    if (archi) {
        fseek(archi, 0, SEEK_END);
        long long totalRegistros = ftell(archi) / sizeof(stPartidaXJugador);
        if (totalRegistros > 0) {
            fseek(archi, -1 * (long long)sizeof(stPartidaXJugador), SEEK_END);
            fread(&aux, sizeof(stPartidaXJugador), 1, archi);
            ultimoID = aux.idPartidaJugador;
        }
        fclose(archi);
    }

    // Generar y guardar la partida por jugador
    int resultado = rand() % 3; // Simulado para máquina
    stPartidaXJugador pxj = generarPartidaXJugador(ultimoID + 1, idPartida, jugador.idJugador, resultado);
    guardarPartidasxJugadorEnArchivo(AR_PARTIDASXJUGADOR, &pxj, 1);

    // Actualizar puntos del jugador
    jugador.ptsTotales += pxj.puntosJugador;
    guardarCambiosJugador(jugador);

    printf("DEBUG: Partida por jugador guardada - ID Partida: %d, ID Jugador: %d, Resultado: %d, Puntos: %d\n",
           pxj.idPartida, pxj.idJugador, pxj.resultado, pxj.puntosJugador);
}

void generarPartidaXJugadorParaVersus(stJugador jugador1, stJugador jugador2, int idPartida, int resultadoPartida) {
    FILE *archi = fopen(AR_PARTIDASXJUGADOR, "rb");
    int ultimoID = 0;
    stPartidaXJugador aux;

    // Obtener el último ID de partida por jugador
    if (archi) {
        fseek(archi, 0, SEEK_END);
        long long totalRegistros = ftell(archi) / sizeof(stPartidaXJugador);
        if (totalRegistros > 0) {
            fseek(archi, -1 * (long long)sizeof(stPartidaXJugador), SEEK_END);
            fread(&aux, sizeof(stPartidaXJugador), 1, archi);
            ultimoID = aux.idPartidaJugador;
        }
        fclose(archi);
    }

    // Determinar resultados para cada jugador
    int resultado1, resultado2;
    if (resultadoPartida == 1) { // Jugador 1 gana
        resultado1 = 1; // Victoria
        resultado2 = 0; // Derrota
    } else if (resultadoPartida == 2) { // Jugador 2 gana
        resultado1 = 0; // Derrota
        resultado2 = 1; // Victoria
    } else { // Empate
        resultado1 = 2; // Empate
        resultado2 = 2; // Empate
    }

    // Generar y guardar partida para Jugador 1
    stPartidaXJugador pxj1 = generarPartidaXJugador(ultimoID + 1, idPartida, jugador1.idJugador, resultado1);
    guardarPartidasxJugadorEnArchivo(AR_PARTIDASXJUGADOR, &pxj1, 1);
    jugador1.ptsTotales += pxj1.puntosJugador;
    guardarCambiosJugador(jugador1);
    printf("DEBUG: Partida para Jugador 1 (%s) - ID Partida: %d, Resultado: %d, Puntos: %d\n",
           jugador1.username, idPartida, pxj1.resultado, pxj1.puntosJugador);

    // Generar y guardar partida para Jugador 2
    stPartidaXJugador pxj2 = generarPartidaXJugador(ultimoID + 2, idPartida, jugador2.idJugador, resultado2);
    guardarPartidasxJugadorEnArchivo(AR_PARTIDASXJUGADOR, &pxj2, 1);
    jugador2.ptsTotales += pxj2.puntosJugador;
    guardarCambiosJugador(jugador2);
    printf("DEBUG: Partida para Jugador 2 (%s) - ID Partida: %d, Resultado: %d, Puntos: %d\n",
           jugador2.username, idPartida, pxj2.resultado, pxj2.puntosJugador);
}

void mostrarHistorialPartidasJugador(int idJugador) {
    FILE *archi = fopen(AR_PARTIDASXJUGADOR, "rb");
    if (archi) {
        stPartidaXJugador pxj;
        printf("\n--- Historial de partidas del jugador ID %d ---\n", idJugador);
        int found = 0;
        while (fread(&pxj, sizeof(stPartidaXJugador), 1, archi) == 1) {
            if (pxj.idJugador == idJugador) {
                imprimirPartidasporJugador(pxj);
                found = 1;
            }
        }
        if (!found) {
            printf("No se encontraron partidas para el jugador ID %d.\n", idJugador);
        }
        fclose(archi);
    } else {
        printf("Error al abrir el archivo %s.\n", AR_PARTIDASXJUGADOR);
    }
}

/** Hecha por Luciana. Guarda partidas en archivo, actualiza los registros de los jugadores involucrados **/
void guardarPartidaYRegistros(stJugador *j1, stJugador *j2, int resultado1, int resultado2, const char *modo) {
    int idPartida = obtenerUltimoIDPartida() + 1;

    stPartida partida = {0};
    partida.idPartida = idPartida;
    partida.esContraCpu = (j2 == NULL) ? 1 : 0;
    strcpy(partida.dificultad, modo);

    guardarPartidasEnArchivo("partidas.dat", &partida, 1);

    stPartidaXJugador pxj[2];
    pxj[0] = generarPartidaXJugador(idPartida * 2 - 1, idPartida, j1->idJugador, resultado1);

    int cantidad = 1;

    if (j2 != NULL) {
        pxj[1] = generarPartidaXJugador(idPartida * 2, idPartida, j2->idJugador, resultado2);
        cantidad = 2;
    }

    guardarPartidasxJugadorEnArchivo(AR_PARTIDASXJUGADOR, pxj, cantidad);

    j1->ptsTotales += pxj[0].puntosJugador;
    guardarCambiosJugador(*j1); // Reemplazado actualizarJugadorEnArchivo por guardarCambiosJugador

    if (j2 != NULL) {
        j2->ptsTotales += pxj[1].puntosJugador;
        guardarCambiosJugador(*j2); // Reemplazado actualizarJugadorEnArchivo por guardarCambiosJugador
    }
}

/** Hecha por Luciana. Genera partidas por jugador de manera aleatoria según cantidad indicada **/
void generarYGuardarPartidasXJugadorAutom(int cantidad) {
    stPartidaXJugador *registros = malloc(cantidad * sizeof(stPartidaXJugador));
    if (!registros) {
        printf("Error al reservar memoria.\n");
        return;
    }

    int ultimoID = obtenerUltimoIdPartidaXJugador();

    for (int i = 0; i < cantidad; i++) {
        int idPartida = rand() % 1000 + 1;   // podés reemplazar por un id real
        int idJugador = rand() % 2000 + 1;   // idem
        int resultado = rand() % 3;

        registros[i] = generarPartidaXJugador(ultimoID + i + 1, idPartida, idJugador, resultado);
    }

    guardarPartidasxJugadorEnArchivo(AR_PARTIDASXJUGADOR, registros, cantidad);
    free(registros);
}
