#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"
#include "jugador.h"
#include "tateti.h"
#include "mock.h"
#include <locale.h>

// ========== LOGIN ==========

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
        printf("DEBUG: Username ingresado (post-minusculas): '%s'\n", username);
    } while (strlen(username) == 0);

    do {
        printf("Password: ");
        fflush(stdin);
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';
        printf("DEBUG: Password ingresado: '%s'\n", password);
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
        printf("\n❌ Usuario y/o contraseña incorrectos o cuenta eliminada.\n");
        return 0;
    }

    printf("\n✅ ¡Bienvenido %s %s!\n", jugadorLogueado->nombre, jugadorLogueado->apellido);
    return 1;
}

// ========== FUNCIONES EXTRAS ==========

void jugarContraMaquina(stJugador* jugador) {
    printf("🕹 Jugando contra la máquina...\n");
}

void jugarContraJugador(stJugador* jugador) {
    printf("🎮 Jugando contra otro jugador...\n");
}

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
            printf("\n🗑 Cuenta eliminada correctamente.\n");
            encontrado = 1;
            break;
        }
    }

    fclose(arch);
    if (!encontrado) {
        printf("No se pudo eliminar la cuenta.\n");
    }
}

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
