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
#include "ranking.h" // Nueva inclusión

#define ARCHIVO_JUGADORES "jugadores.dat"
#define AR_PARTIDAS "partidas.dat"
#define AR_PARTIDASXJUGADOR "partidasxjugador.dat"

int mostrarSubmenuAutenticacion(stJugador *jugador, int jugadorNumero) {
    int opcion;
    printf("\n=== Autenticación Jugador %d ===\n", jugadorNumero);
    while (1) {
        printf("1. Registrarse\n");
        printf("2. Iniciar sesion\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while (getchar() != '\n'); // Limpiar búfer

        switch (opcion) {
            case 1: {
                int ultimoID = obtenerUltimoID();
                *jugador = cargarUnJugador(ultimoID);
                guardarJugadorArchivo(*jugador);
                printf("\n Jugador %d registrado con exito!\n", jugadorNumero);
                //imprimirJugadoresArchivo(); // Depuración
                return 1; // Autenticado
            }
            case 2: {
                if (loginJugador(jugador)) {
                    printf("\n Jugador %d autenticado correctamente!\n", jugadorNumero);
                    return 1; // Autenticado
                }
                printf("\n Error en inicio de sesión. Intenta de nuevo.\n");
                break;
            }
            case 3: {
                printf("\n Autenticación cancelada para Jugador %d.\n", jugadorNumero);
                return 0; // No autenticado
            }
            default:
                printf(" Opcion no valida. Intenta de nuevo.\n");
        }
    }
}

int main() {
    setlocale(LC_ALL, "");
    srand(time(NULL)); // Inicializar la semilla para rand()

    int opcion, salir = 0;

    while (!salir) {
        printf("\n============== Menu Principal ==============\n");
        printf("1. Registrarse\n");
        printf("2. Iniciar sesion\n");
        printf("3. Salir\n");

        /** Luciana agregó estas opciones para poder probar la correcta persistencia de los archivos**/
        printf("4. Ver archivo jugadores\n");
        printf("5. Ver archivo partidas\n");
        printf("6. Ver archivo partidas por jugador\n");
        printf("7. Cargar jugadores\n");
        printf("8. Cargar partidas\n");
        printf("9. Cargar partidas por jugador\n");
        /** **/
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while (getchar() != '\n'); // Consumir el salto de línea

        switch (opcion) {
            case 1: {
                int ultimoID = obtenerUltimoID();
                stJugador nuevoJugador = cargarUnJugador(ultimoID);
                guardarJugadorArchivo(nuevoJugador);
                printf("\n ¡Registrado con éxito!\n");
                //imprimirJugadoresArchivo(); // Depuración
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
                        printf("6. Cambiar mi username\n");
                        printf("7. Ver mis estadísticas y ranking\n"); // Nueva opción
                        printf("Seleccione una opción: ");
                        scanf("%d", &opcionPostLogin);
                        while (getchar() != '\n'); // Consumir el salto de línea

                        switch (opcionPostLogin) {
                            case 1: {
                                int dificultad;
                                printf("\nSeleccione la dificultad:\n");
                                printf("1. Aprendiz\n");
                                printf("2. Terrorista\n");
                                printf("Opción: ");
                                scanf("%d", &dificultad);
                                while (getchar() != '\n'); // Consumir el salto de línea

                                if (dificultad == 1 || dificultad == 2) {
                                    int resultado = jugar(1, dificultad);
                                    // Generar una partida
                                    stPartida partida;
                                    partida.idPartida = obtenerUltimoIDPartida() + 1;
                                    strcpy(partida.dificultad, dificultad == 1 ? "Aprendiz" : "Terrorista");
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
                                    printf("Dificultad inválida.\n");
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
                                    printf(" Partida cancelada: Jugador 2 no autenticado.\n");
                                    break;
                                }

                                // Verificar que los jugadores sean diferentes
                                if (jugador1.idJugador == jugador2.idJugador) {
                                    printf("No puedes jugar contra ti mismo.\n");
                                    break;
                                }

                                // Generar una partida
                                stPartida partida;
                                partida.idPartida = obtenerUltimoIDPartida() + 1;
                                strcpy(partida.dificultad, "Vs Jugador");
                                partida.esContraCpu = 0;
                                FILE *partidasFile = fopen(AR_PARTIDAS, "ab");
                                if (partidasFile) {
                                    fwrite(&partida, sizeof(stPartida), 1, partidasFile);
                                    fclose(partidasFile);
                                    printf("Partida guardada en %s - ID: %d\n", AR_PARTIDAS, partida.idPartida);
                                } else {
                                    printf("No se pudo abrir %s para guardar la partida.\n", AR_PARTIDAS);
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
                                printf("\n Sesión cerrada.\n");
                                break;
                            }
                            case 5: {
                                mostrarHistorialPartidasJugador(jugadorLogueado.idJugador);
                                break;
                            }
                            case 6: {
                                cambiarUsername(&jugadorLogueado); // Nueva funcionalidad para cambiar username
                                break;
                            }
                            case 7: {
                                mostrarEstadisticasJugador(jugadorLogueado.idJugador); // Nueva funcionalidad
                                mostrarRankingJugadores(); // Mostrar ranking
                                break;
                            }
                            default:
                                printf(" Opcion no valida.\n");
                        }
                    }
                }
                break;
            }
            case 3: {
                salir = 1;
                printf("\n ¡Gracias por jugar!\n");
                break;
            }

            case 4:
                printf("\n--- Contenido de %s ---\n", ARCHIVO_JUGADORES);
                leerJugadoresDesdeArchivo(ARCHIVO_JUGADORES);
                break;

            case 5:
                printf("\n--- Contenido de %s ---\n", AR_PARTIDAS);
                leerPartidasDesdeArchivo(AR_PARTIDAS);
                break;

            case 6:
                printf("\n--- Contenido de %s ---\n", AR_PARTIDASXJUGADOR);
                leerPartidasPorJugadorDesdeArchivo(AR_PARTIDASXJUGADOR);
                break;

            case 7: {
                int n;
                printf("¿Cuántos jugadores generar? ");
                scanf("%d", &n);
                generarYGuardarJugadores(n);
                break;
            }

            case 8: {
                int n;
                printf("Partidas a generar ");
                scanf("%d", &n);
                generarYGuardarPartidas(n);
                break;
            }
            case 9: {
                int n;
                printf("Partidas por jugador a generar: ");
                scanf("%d", &n);
                generarYGuardarPartidasXJugadorAutom(n);  // Llamamos a la función nueva
                break;
            }

            default:
                printf("Opción no válida.\n");
        }
    }

    return 0;
}
