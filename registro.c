#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"
#include "jugador.h"
#include <locale.h>
#include "mock.h"

// ========== FUNCIÓN DE REGISTRO ==========
stJugador cargarUnJugador(int ultimoID) {
    stJugador aux;
    memset(&aux, 0, sizeof(stJugador)); // Inicializar para evitar basura

    aux.idJugador = ultimoID + 1;
    aux.ptsTotales = 0;
    aux.eliminado = 0;

    do {
        printf("Ingrese su nombre: ");
        fflush(stdin);
        fgets(aux.nombre, sizeof(aux.nombre), stdin);
        aux.nombre[strcspn(aux.nombre, "\n")] = '\0';
        printf("DEBUG: Nombre ingresado: '%s'\n", aux.nombre);
        if (strlen(aux.nombre) == 0 || !validarSoloLetras(aux.nombre)) {
            printf("❌ Nombre inválido. No puede estar vacío y debe contener solo letras.\n");
        }
    } while (strlen(aux.nombre) == 0 || !validarSoloLetras(aux.nombre));

    do {
        printf("Ingrese su apellido: ");
        fflush(stdin);
        fgets(aux.apellido, sizeof(aux.apellido), stdin);
        aux.apellido[strcspn(aux.apellido, "\n")] = '\0';
        printf("DEBUG: Apellido ingresado: '%s'\n", aux.apellido);
        if (strlen(aux.apellido) == 0 || !validarSoloLetras(aux.apellido)) {
            printf("❌ Apellido inválido. No puede estar vacío y debe contener solo letras.\n");
        }
    } while (strlen(aux.apellido) == 0 || !validarSoloLetras(aux.apellido));

    do {
        printf("Ingrese su email: ");
        fflush(stdin);
        fgets(aux.email, sizeof(aux.email), stdin);
        aux.email[strcspn(aux.email, "\n")] = '\0';
        printf("DEBUG: Email ingresado: '%s'\n", aux.email);
        if (!validarEmail(aux.email)) {
            printf("❌ Email inválido. Debe contener '@' y '.'.\n");
        }
    } while (!validarEmail(aux.email));

    do {
        printf("Ingrese su nombre de usuario: ");
        fflush(stdin);
        fgets(aux.username, sizeof(aux.username), stdin);
        aux.username[strcspn(aux.username, "\n")] = '\0';
        convertirMinusculas(aux.username);
        printf("DEBUG: Username ingresado (post-minusculas): '%s'\n", aux.username);
        if (strlen(aux.username) == 0) {
            printf("❌ Usuario inválido. No puede estar vacío.\n");
        } else if (existeUsernameEnArchivo(aux.username)) {
            printf("❌ Ese nombre de usuario ya está registrado. Elija otro.\n");
        }
    } while (strlen(aux.username) == 0 || existeUsernameEnArchivo(aux.username));

    do {
        printf("Ingrese su contraseña (mínimo una mayúscula y una minúscula): ");
        fflush(stdin);
        fgets(aux.password, sizeof(aux.password), stdin);
        aux.password[strcspn(aux.password, "\n")] = '\0';
        printf("DEBUG: Password ingresado: '%s'\n", aux.password);
        if (!validarPassword(aux.password)) {
            printf("❌ Contraseña inválida. Debe tener una mayúscula y una minúscula.\n");
        }
    } while (!validarPassword(aux.password));

    do {
        printf("Ingrese su DNI: ");
        fflush(stdin);
        fgets(aux.dni, sizeof(aux.dni), stdin);
        aux.dni[strcspn(aux.dni, "\n")] = '\0';
        printf("DEBUG: DNI ingresado: '%s'\n", aux.dni);
        if (!validarDNI(aux.dni)) {
            printf("❌ DNI inválido. Debe contener solo números y tener entre 7 y 9 dígitos.\n");
        }
    } while (!validarDNI(aux.dni));

    do {
        printf("Ingrese su nacionalidad o país: ");
        fflush(stdin);
        fgets(aux.pais, sizeof(aux.pais), stdin);
        aux.pais[strcspn(aux.pais, "\n")] = '\0';
        printf("DEBUG: Pais ingresado: '%s'\n", aux.pais);
        if (strlen(aux.pais) == 0 || !validarSoloLetras(aux.pais)) {
            printf("❌ Nacionalidad inválida. Debe contener solo letras.\n");
        }
    } while (strlen(aux.pais) == 0 || !validarSoloLetras(aux.pais));

    printf("\n✅ ¡Registro completado con éxito!\n");
    system("pause");
    system("cls");

    return aux;
}

// ========== FUNCIONES DE VALIDACIÓN ==========

int validarSoloLetras(char cadena[]) {
    int i = 0, valido = 1;
    while (cadena[i] != '\0' && valido == 1) {
        if (!((cadena[i] >= 65 && cadena[i] <= 90) || (cadena[i] >= 97 && cadena[i] <= 122))) {
            valido = 0;
        }
        i++;
    }
    return valido;
}

int validarPassword(char clave[]) {
    int i = 0, tieneMayuscula = 0, tieneMinuscula = 0, valido = 0;
    while (clave[i] != '\0') {
        if (clave[i] >= 65 && clave[i] <= 90) tieneMayuscula = 1;
        if (clave[i] >= 97 && clave[i] <= 122) tieneMinuscula = 1;
        i++;
    }
    if (tieneMayuscula && tieneMinuscula) valido = 1;
    return valido;
}

int validarEmail(char correo[]) {
    int i = 0, tieneArroba = 0, tienePunto = 0, valido = 0;
    while (correo[i] != '\0') {
        if (correo[i] == '@') tieneArroba = 1;
        if (correo[i] == '.') tienePunto = 1;
        i++;
    }
    if (tieneArroba && tienePunto) valido = 1;
    return valido;
}

int validarDNI(char dni[]) {
    int i = 0, valido = 1, longitud = strlen(dni);
    if (longitud < 7 || longitud > 9) {
        valido = 0;
    } else {
        while (dni[i] != '\0' && valido == 1) {
            if (!(dni[i] >= 48 && dni[i] <= 57)) {
                valido = 0;
            }
            i++;
        }
    }
    return valido;
}

void convertirMinusculas(char cadena[]) {
    int i = 0;
    while (cadena[i] != '\0') {
        if (cadena[i] >= 65 && cadena[i] <= 90) {
            cadena[i] += 32;
        }
        i++;
    }
}

// ========== FUNCIONES DE ARCHIVO ==========

int obtenerUltimoID() {
    FILE* archivo = fopen("jugadores.dat", "rb");
    stJugador aux;
    int ultimoID = 0;

    if (archivo != NULL) {
        fseek(archivo, 0, SEEK_END);
        int totalJugadores = ftell(archivo) / sizeof(stJugador);
        if (totalJugadores > 0) {
            fseek(archivo, -1 * sizeof(stJugador), SEEK_END);
            fread(&aux, sizeof(stJugador), 1, archivo);
            ultimoID = aux.idJugador;
        }
        fclose(archivo);
    }

    return ultimoID;
}

void guardarJugadorArchivo(stJugador jugador) {
    FILE* archivo = fopen("jugadores.dat", "ab");
    if (archivo != NULL) {
        fwrite(&jugador, sizeof(stJugador), 1, archivo);
        fclose(archivo);
        printf("DEBUG: Jugador guardado - Username: '%s', Password: '%s'\n", jugador.username, jugador.password); // Depuración
    } else {
        printf("Error al abrir el archivo.\n");
    }
}

int existeUsernameEnArchivo(char username[]) {
    FILE* archivo = fopen(ARCHIVO_JUGADORES, "rb");
    stJugador aux;
    int existe = 0;

    if (archivo != NULL) {
        while (fread(&aux, sizeof(stJugador), 1, archivo) > 0) {
            if (strcmpi(aux.username, username) == 0 && aux.eliminado == 0) {
                existe = 1;
                break;
            }
        }
        fclose(archivo);
    }

    return existe;
}

// ========== DEPURACIÓN ==========

void imprimirJugadoresArchivo() {
    FILE* arch = fopen(ARCHIVO_JUGADORES, "rb");
    stJugador aux;
    if (arch) {
        printf("\n--- Contenido de jugadores.dat ---\n");
        while (fread(&aux, sizeof(stJugador), 1, arch) > 0) {
            printf("ID: %d\n", aux.idJugador);
            printf("Nombre: %s\n", aux.nombre);
            printf("Apellido: %s\n", aux.apellido);
            printf("Email: %s\n", aux.email);
            printf("Username: %s\n", aux.username);
            printf("Password: %s\n", aux.password);
            printf("DNI: %s\n", aux.dni);
            printf("Pais: %s\n", aux.pais);
            printf("Puntos: %d\n", aux.ptsTotales);
            printf("Eliminado: %d\n", aux.eliminado);
            printf("------------------------\n");
        }
        fclose(arch);
    } else {
        printf("Error al abrir jugadores.dat para depuración.\n");
    }
}
