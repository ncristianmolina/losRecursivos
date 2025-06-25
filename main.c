#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "jugador.h"
#include "registro.h"
#include "inicio-sesion.h"
#include "tateti.h"
#include "mock.h"
#include "partidas.h"
#include "partidasXjugador.h"

#define ARCHIVO_JUGADORES "jugadores.dat"
#define AR_PARTIDAS "partidas.dat"
#define AR_PARTIDASXJUGADOR "partidasxjugador.dat"
#define TOTAL_JUGADORES 10
#define NUM_JUGADORES_CARGADOS 4

int obtenerUltimoIdPartida() {
    FILE *archi = fopen(AR_PARTIDAS, "rb");
    int ultimoID = 0;

    if (archi == NULL) {
        printf("DEBUG: No se pudo abrir %s. Iniciando con ID 0.\n", AR_PARTIDAS);
        return ultimoID;
    }

    // Obtener tamaño del archivo
    fseek(archi, 0, SEEK_END);
    long long fileSize = ftell(archi);
    if (fileSize == -1) {
        printf("DEBUG: Error en ftell para %s. Iniciando con ID 0.\n", AR_PARTIDAS);
        fclose(archi);
        return ultimoID;
    }

    // Calcular número de registros
    long long totalPartidas = fileSize / sizeof(stPartida);
    if (totalPartidas > 0) {
        fseek(archi, -1 * (long long)sizeof(stPartida), SEEK_END);
        stPartida aux;
        if (fread(&aux, sizeof(stPartida), 1, archi) == 1) {
            ultimoID = aux.idPartida;
            printf("DEBUG: Último ID de partida encontrado: %d\n", ultimoID);
        } else {
            printf("DEBUG: Error al leer la última partida en %s.\n", AR_PARTIDAS);
        }
    }

    fclose(archi);
    return ultimoID;
}

int mostrarSubmenuAutenticacion(stJugador *jugador, int jugadorNumero) {
    int opcion;
    printf("\n=== Autenticación Jugador %d ===\n", jugadorNumero);
    while (1) {
        printf("1. Registrarse\n");
        printf("2. Iniciar sesión\n");
        printf("3. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        while (getchar() != '\n'); // Limpiar búfer

        switch (opcion) {
            case 1: {
                int ultimoID = obtenerUltimoID();
                *jugador = cargarUnJugador(ultimoID);
                guardarJugadorArchivo(*jugador);
                printf("\n✅ Jugador %d registrado con éxito!\n", jugadorNumero);
                imprimirJugadoresArchivo(); // Depuración
                return 1; // Autenticado
            }
            case 2: {
                if (loginJugador(jugador)) {
                    printf("\n✅ Jugador %d autenticado correctamente!\n", jugadorNumero);
                    return 1; // Autenticado
                }
                printf("\n❌ Error en inicio de sesión. Intenta de nuevo.\n");
                break;
            }
            case 3: {
                printf("\n👋 Autenticación cancelada para Jugador %d.\n", jugadorNumero);
                return 0; // No autenticado
            }
            default:
                printf("❌ Opción no válida. Intenta de nuevo.\n");
        }
    }
}

int main() {
    setlocale(LC_ALL, "Spanish");
    srand(time(NULL)); // Inicializar la semilla para rand()

    int opcion, salir = 0;

    while (!salir) {
        printf("\n============== Menú Principal ==============\n");
        printf("1. Registrarse\n");
        printf("2. Iniciar sesión\n");
        printf("3. Salir\n");
        printf("4. Ver ranking\n");
        printf("5. Generar partidas mock\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        while (getchar() != '\n'); // Consumir el salto de línea

        switch (opcion) {
            case 1: {
                int ultimoID = obtenerUltimoID();
                stJugador nuevoJugador = cargarUnJugador(ultimoID);
                guardarJugadorArchivo(nuevoJugador);
                printf("\n✅ ¡Registrado con éxito!\n");
                imprimirJugadoresArchivo(); // Depuración
                break;
            }
            case 2: {
                stJugador jugadorLogueado;
                if (loginJugador(&jugadorLogueado)) {
                    int opcionPostLogin;
                    int cerrarSesion = 0;

                    while (!cerrarSesion) {
                        printf("\n============ Menú del Jugador (%s) ============\n", jugadorLogueado.username);
                        printf("1. Jugar contra la máquina\n");
                        printf("2. Jugar contra otro jugador\n");
                        printf("3. Eliminar mi cuenta\n");
                        printf("4. Cerrar sesión\n");
                        printf("5. Ver mi historial de partidas\n");
                        printf("Seleccione una opción: ");
                        scanf("%d", &opcionPostLogin);
                        while (getchar() != '\n'); // Consumir el salto de línea

                        switch (opcionPostLogin) {
                            case 1: {
                                int dificultad;
                                printf("\nSeleccione la dificultad:\n");
                                printf("1. Fácil\n");
                                printf("2. Difícil\n");
                                printf("Opción: ");
                                scanf("%d", &dificultad);
                                while (getchar() != '\n'); // Consumir el salto de línea

                                if (dificultad == 1 || dificultad == 2) {
                                    int resultado = jugar(1, dificultad);
                                    // Generar una partida
                                    stPartida partida;
                                    partida.idPartida = obtenerUltimoIdPartida() + 1;
                                    strcpy(partida.dificultad, dificultad == 1 ? "Fácil" : "Difícil");
                                    partida.esContraCpu = 1;
                                    FILE *partidasFile = fopen(AR_PARTIDAS, "ab");
                                    if (partidasFile) {
                                        fwrite(&partida, sizeof(stPartida), 1, partidasFile);
                                        fclose(partidasFile);
                                        printf("DEBUG: Partida guardada en %s - ID: %d\n", AR_PARTIDAS, partida.idPartida);
                                    } else {
                                        printf("DEBUG: No se pudo abrir %s para guardar la partida.\n", AR_PARTIDAS);
                                    }
                                    // Ajustar resultado para el jugador (vs Bot)
                                    int resultadoJugador = (resultado == 1) ? 1 : (resultado == 0 ? 2 : 0); // Victoria, empate o derrota
                                    stPartidaXJugador pxj = generarPartidaXJugador(obtenerUltimoIdPartidaXJugador() + 1, partida.idPartida, jugadorLogueado.idJugador, resultadoJugador);
                                    guardarPartidasxJugadorEnArchivo(AR_PARTIDASXJUGADOR, &pxj, 1);
                                    jugadorLogueado.ptsTotales += pxj.puntosJugador;
                                    guardarCambiosJugador(jugadorLogueado);
                                    printf("DEBUG: Partida para Jugador %s - ID Partida: %d, Resultado: %d, Puntos: %d\n",
                                           jugadorLogueado.username, partida.idPartida, pxj.resultado, pxj.puntosJugador);
                                } else {
                                    printf("❌ Dificultad inválida.\n");
                                }
                                break;
                            }
                            case 2: {
                                // Autenticar Jugador 1 (ya logueado)
                                stJugador jugador1 = jugadorLogueado;
                                printf("Jugador 1: %s (ID: %d) autenticado.\n", jugador1.username, jugador1.idJugador);

                                // Autenticar Jugador 2
                                stJugador jugador2;
                                if (!mostrarSubmenuAutenticacion(&jugador2, 2)) {
                                    printf("❌ Partida cancelada: Jugador 2 no autenticado.\n");
                                    break;
                                }

                                // Verificar que los jugadores sean diferentes
                                if (jugador1.idJugador == jugador2.idJugador) {
                                    printf("❌ No puedes jugar contra ti mismo.\n");
                                    break;
                                }

                                // Generar una partida
                                stPartida partida;
                                partida.idPartida = obtenerUltimoIdPartida() + 1;
                                strcpy(partida.dificultad, "Vs Jugador");
                                partida.esContraCpu = 0;
                                FILE *partidasFile = fopen(AR_PARTIDAS, "ab");
                                if (partidasFile) {
                                    fwrite(&partida, sizeof(stPartida), 1, partidasFile);
                                    fclose(partidasFile);
                                    printf("DEBUG: Partida guardada en %s - ID: %d\n", AR_PARTIDAS, partida.idPartida);
                                } else {
                                    printf("DEBUG: No se pudo abrir %s para guardar la partida.\n", AR_PARTIDAS);
                                }

                                // Jugar y obtener el resultado
                                int resultado = jugar(0, 0); // Modo dos jugadores
                                generarPartidaXJugadorParaVersus(jugador1, jugador2, partida.idPartida, resultado);
                                break;
                            }
                            case 3: {
                                eliminarCuenta(&jugadorLogueado);
                                cerrarSesion = 1;
                                break;
                            }
                            case 4: {
                                cerrarSesion = 1;
                                printf("\n👋 Sesión cerrada.\n");
                                break;
                            }
                            case 5: {
                                mostrarHistorialPartidasJugador(jugadorLogueado.idJugador);
                                break;
                            }
                            default:
                                printf("❌ Opción no válida.\n");
                        }
                    }
                }
                break;
            }
            case 3: {
                salir = 1;
                printf("\n👋 ¡Gracias por jugar!\n");
                break;
            }
            case 4: {
                mostrarRankingJugadores();
                break;
            }
            case 5: {
                // Generar datos mock
                stJugador jugadores[1000];
                stPartida partidas[100];
                int cantJugadores = 0, cantPartidas = 0;

                // Leer jugadores
                FILE *jugadoresFile = fopen(ARCHIVO_JUGADORES, "rb");
                if (jugadoresFile) {
                    while (fread(&jugadores[cantJugadores], sizeof(stJugador), 1, jugadoresFile) == 1 && cantJugadores < 1000) {
                        if (!jugadores[cantJugadores].eliminado) {
                            cantJugadores++;
                        }
                    }
                    fclose(jugadoresFile);
                } else {
                    printf("DEBUG: No se pudo abrir %s para leer jugadores.\n", ARCHIVO_JUGADORES);
                }

                // Leer partidas
                FILE *partidasFile = fopen(AR_PARTIDAS, "rb");
                if (partidasFile) {
                    while (fread(&partidas[cantPartidas], sizeof(stPartida), 1, partidasFile) == 1 && cantPartidas < 100) {
                        cantPartidas++;
                    }
                    fclose(partidasFile);
                } else {
                    printf("DEBUG: No se pudo abrir %s para leer partidas.\n", AR_PARTIDAS);
                }

                if (cantJugadores > 0 && cantPartidas > 0) {
                    generarYGuardarPartidasXJugador(AR_PARTIDASXJUGADOR, jugadores, cantJugadores, partidas, cantPartidas);
                    printf("✅ Partidas mock generadas con éxito.\n");
                } else {
                    printf("❌ No hay suficientes jugadores o partidas para generar datos mock.\n");
                }
                break;
            }
            default:
                printf("❌ Opción no válida.\n");
        }
    }

    return 0;
}
