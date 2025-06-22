#include <stdio.h>
#include <stdlib.h>
#include "inicio-sesion.h"
#include "registro.h"
#include "tateti.h"
#include "jugador.h"
#include "mock.h"
#include <locale.h>

#define AR_JUGADORES "jugadores.dat"
#define AR_PARTIDAS "partidas.dat"

int main() {
    setlocale(LC_ALL, "");
    int opcion;
    int salir = 0;

    while (!salir) {
        printf("\n============== MENU PRINCIPAL ==============\n");
        printf("1. Registrarse\n");
        printf("2. Iniciar sesion\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        fflush(stdin);

        switch (opcion) {
            case 1: {
                int ultimoID = obtenerUltimoID();
                stJugador nuevoJugador = cargarUnJugador(ultimoID);
                guardarJugadorArchivo(nuevoJugador);
                printf("\n✅ ¡Jugador registrado con éxito!\n");
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
                        fflush(stdin);

                        switch (opcionPostLogin) {
                            case 1:
                                jugar(1); // contra la máquina
                                break;
                            case 2:
                                jugar(0); // contra otro jugador
                                break;
                            case 3:
                                eliminarCuenta(&jugadorLogueado);
                                cerrarSesion = 1; // se desloguea tras eliminar
                                break;
                            case 4:
                                cerrarSesion = 1;
                                printf("\n👋 Sesión cerrada.\n");
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
                printf("\n👋 ¡Gracias por usar el sistema!\n");
                break;
            default:
                printf("❌ Opción no válida. Intente de nuevo.\n");
        }
    }

    stJugador todosLosJugadores[TOTAL_JUGADORES];

    /// Copiar los jugadores precargados al arreglo total
    /*for (int i = 0; i < NUM_JUGADORES_PRECARGADOS; i++) {
        todosLosJugadores[i] = jugadoresPrecargados[i];
    }///*/

    // Generar jugadores aleatorios
    for (int i = NUM_JUGADORES_CARGADOS; i < TOTAL_JUGADORES; i++) {
        generarJugadorAleatorio(&todosLosJugadores[i], i + 1);
    }

    // Mostrar todos los jugadores
    for (int i = 0; i < TOTAL_JUGADORES; i++) {
        imprimirJugador(todosLosJugadores[i]);
    }

    guardarJugadoresEnArchivo(AR_JUGADORES, todosLosJugadores, TOTAL_JUGADORES);
    leerJugadoresDesdeArchivo(AR_JUGADORES);
    printf("Guardando archivo en ruta: %s\n", AR_JUGADORES);



    return 0;
}
