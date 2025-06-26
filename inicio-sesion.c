#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"
#include "jugador.h"
#include "tateti.h"
#include "mock.h"
#include <locale.h>

// ========== LOGIN ==========

/* Hecho por Cristian. Autentica usuario con credenciales. */
int loginJugador(stJugador* jugadorLogueado) {
    char username[30], password[20];
    FILE* arch = fopen(ARCHIVO_JUGADORES, "rb");

    if (!arch) {
        printf("Error al abrir archivo de jugadores.\n");
        return 0;
    }

    printf("\n----- INICIO DE SESION -----\n");
    do {
        printf("Username: ");
        fflush(stdin);
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';
        convertirMinusculas(username);
    } while (strlen(username) == 0);

    do {
        printf("Password: ");
        fflush(stdin);
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';
    } while (strlen(password) == 0);

    stJugador aux;
    int encontrado = 0;

    while (fread(&aux, sizeof(stJugador), 1, arch) > 0) {
        if (strcmp(aux.username, username) == 0 && strcmp(aux.password, password) == 0 && aux.eliminado == 0) {
            *jugadorLogueado = aux;
            encontrado = 1;
            break;
        }
    }

    fclose(arch);

    if (!encontrado) {
        printf("\ Usuario y/o contrasenia incorrectos o cuenta eliminada.\n");
        return 0;
    }

    printf("\n¡Bienvenido %s %s!\n", jugadorLogueado->nombre, jugadorLogueado->apellido);
    return 1;
}

// ========== FUNCIONES EXTRAS ==========

/* Hecho por Cristian. Inicia juego contra máquina. */
void jugarContraMaquina(stJugador* jugador) {
    printf("Jugando contra la máquina...\n");
}

/* Hecho por Cristian. Inicia juego contra jugador. */
void jugarContraJugador(stJugador* jugador) {
    printf("Jugando contra otro jugador...\n");
}

/* Hecho por Cristian. Marca cuenta como eliminada. */
void eliminarCuenta(stJugador* jugador) {
    FILE* arch = fopen(ARCHIVO_JUGADORES, "rb+");
    if (!arch) {
        printf("Error al abrir archivo para eliminar cuenta.\n");
        return;
    }

    stJugador aux;
    int encontrado = 0;
    while (fread(&aux, sizeof(stJugador), 1, arch) > 0) {
        if (aux.idJugador == jugador->idJugador) {
            aux.eliminado = 1;
            fseek(arch, -sizeof(stJugador), SEEK_CUR);
            fwrite(&aux, sizeof(stJugador), 1, arch);
            printf("\n Cuenta eliminada correctamente.\n");
            encontrado = 1;
            break;
        }
    }

    fclose(arch);
    if (!encontrado) {
        printf("No se pudo eliminar la cuenta.\n");
    }
}

/* Hecho por Cristian. Actualiza datos jugador archivo. */
void guardarCambiosJugador(stJugador jugadorActualizado) {
    FILE* archi = fopen(ARCHIVO_JUGADORES, "rb+");
    if (!archi) {
        printf("Error al abrir archivo para guardar cambios.\n");
        return;
    }

    stJugador aux;
    while (fread(&aux, sizeof(stJugador), 1, archi) > 0) {
        if (aux.idJugador == jugadorActualizado.idJugador) {
            fseek(archi, -sizeof(stJugador), SEEK_CUR);
            fwrite(&jugadorActualizado, sizeof(stJugador), 1, archi);
            break;
        }
    }

    fclose(archi);
}

/* Hecho por Cristian. Modifica username jugador archivo. */
void cambiarUsername(stJugador* jugador) {
    char nuevoUsername[30];
    printf("\n----- CAMBIAR USERNAME -----\n");
    do {
        printf("Ingrese nuevo username: ");
        fflush(stdin);
        fgets(nuevoUsername, sizeof(nuevoUsername), stdin);
        nuevoUsername[strcspn(nuevoUsername, "\n")] = '\0';
        convertirMinusculas(nuevoUsername);
        if (strlen(nuevoUsername) == 0) {
            printf("El username no puede estar vacío.\n");
        } else if (existeUsernameEnArchivo(nuevoUsername)) {
            printf("Ese username ya está en uso. Elija otro.\n");
        }
    } while (strlen(nuevoUsername) == 0 || existeUsernameEnArchivo(nuevoUsername));

    // Actualizar solo el username en la estructura
    strcpy(jugador->username, nuevoUsername);
    guardarCambiosJugador(*jugador);
    printf("\nUsername actualizado a '%s' con éxito!\n", jugador->username);
}
