#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD
#include "inicio-sesion.h"
#include "registro.h"
#include "tateti.h"
#include "jugador.h"
#include "mock.h"
#include "partidas.h"
#include "partidasXjugador.h"
=======
#include <string.h>
>>>>>>> 937ef31 (Funcion login y registro, dificultad facil y dificil)
#include <locale.h>
#include "jugador.h"
#include "registro.h"
#include "inicio-sesion.h"
#include "tateti.h"
#include "mock.h"

#define ARCHIVO_JUGADORES "jugadores.dat"
#define TOTAL_JUGADORES 10
#define NUM_JUGADORES_CARGADOS 4
#define AR_JUGADORES "jugadores.dat"
<<<<<<< HEAD
#define AR_PARTIDAS "partidas.dat"
#define AR_PARTIDASXJUGADOR    "partidasxjugador.dat"
=======
>>>>>>> 937ef31 (Funcion login y registro, dificultad facil y dificil)

int main() {
    setlocale(LC_ALL, "Spanish"); // Configura la codificación para caracteres en español

    int opcion, salir = 0;

    while (!salir) {
        printf("\n============== MENU PRINCIPAL ==============\n");
        printf("1. Registrarse\n");
        printf("2. Iniciar sesion\n");
        printf("3. Salir\n");
        printf("4. Ver archivo jugadores\n");
        printf("5. Ver archivo partidas\n");
        printf("6. Ver archivo partidas por jugador\n");
        printf("7. Cargar jugadores\n");
        printf("8. Cargar partidas\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while (getchar() != '\n'); // Consumir el salto de línea

        switch (opcion) {
            case 1: {
                int ultimoID = obtenerUltimoID();
                stJugador nuevoJugador = cargarUnJugador(ultimoID);
                guardarJugadorArchivo(nuevoJugador);
                printf("\n✅ ¡Jugador registrado con éxito!\n");
                imprimirJugadoresArchivo(); // Depuración
                break;
            }
            case 2: {
                stJugador jugadorLogueado;
                if (loginJugador(&jugadorLogueado)) {
                    int opcionPostLogin;
                    int cerrarSesion = 0;

                    while (!cerrarSesion) {
                        printf("\n============ MENÚ DEL JUGADOR ============\n");
                        printf("1. Jugar contra la máquina\n");
                        printf("2. Jugar contra otro jugador\n");
                        printf("3. Eliminar mi cuenta\n");
                        printf("4. Cerrar sesión\n");
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
                                    jugar(1, dificultad);
                                } else {
                                    printf("❌ Dificultad inválida.\n");
                                }
                                break;
                            }
                            case 2:
                                jugar(0, 0); // modo 2 jugadores, sin dificultad
                                break;
                            case 3:
                                eliminarCuenta(&jugadorLogueado);
                                cerrarSesion = 1;
                                break;
                            case 4:
                                cerrarSesion = 1;
                                printf("\n Sesión cerrada.\n");
                                break;
                            default:
                                printf("❌ Opción no válida.\n");
                        }
                    }
                }
                break;
            }
            case 3:
                salir = 1;
                printf("\n ¡Gracias por usar el sistema!\n");
                break;
                case 4:
                printf("\n--- Contenido de %s ---\n", AR_JUGADORES);
                leerJugadoresDesdeArchivo(AR_JUGADORES);
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


            default:
                printf("❌ Opción no válida. Intente de nuevo.\n");
        }
    }

<<<<<<< HEAD
//    stJugador todosLosJugadores[TOTAL_JUGADORES];

    /// Copiar los jugadores precargados al arreglo total
    /*for (int i = 0; i < NUM_JUGADORES_PRECARGADOS; i++) {
        todosLosJugadores[i] = jugadoresPrecargados[i];
    }///*/

    // Generar jugadores aleatorios
    //for (int i = NUM_JUGADORES_CARGADOS; i < TOTAL_JUGADORES; i++) {
     //   generarJugadorAleatorio(&todosLosJugadores[i], i + 1);
    //}

    // Mostrar todos los jugadores
    //for (int i = 0; i < TOTAL_JUGADORES; i++) {
       // imprimirJugador(todosLosJugadores[i]);
    ////}

    //guardarJugadoresEnArchivo(AR_JUGADORES, todosLosJugadores, TOTAL_JUGADORES);
    //leerJugadoresDesdeArchivo(AR_JUGADORES);
    //printf("Guardando archivo en ruta: %s\n", AR_JUGADORES);


    //stPartida partidas[100];///

    //for (int i = 0; i < 100; i++) {
       // generarPartidaAleatoria(&partidas[i], i + 1);
    //}

    //guardarPartidasEnArchivo(AR_PARTIDAS, partidas, 100);
    //leerPartidasDesdeArchivo(AR_PARTIDAS);
        ///

=======
    // Código de generación aleatoria comentado
    /*
    stJugador todosLosJugadores[TOTAL_JUGADORES];
    for (int i = NUM_JUGADORES_CARGADOS; i < TOTAL_JUGADORES; i++) {
        generarJugadorAleatorio(&todosLosJugadores[i], i + 1);
    }
    for (int i = 0; i < TOTAL_JUGADORES; i++) {
        imprimirJugador(todosLosJugadores[i]);
    }
    guardarJugadoresEnArchivo(AR_JUGADORES, todosLosJugadores, TOTAL_JUGADORES);
    leerJugadoresDesdeArchivo(AR_JUGADORES);
    printf("Guardando archivo en ruta: %s\n", AR_JUGADORES);

    stPartida partidas[100];
    for (int i = 0; i < 100; i++) {
        generarPartidaAleatoria(&partidas[i], i + 1);
    }
    guardarPartidasEnArchivo("partidas.dat", partidas, 100);
    leerPartidasDesdeArchivo("partidas.dat");
    */
>>>>>>> 937ef31 (Funcion login y registro, dificultad facil y dificil)

    return 0;
}
