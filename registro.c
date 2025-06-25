#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "registro.h"
#include "jugador.h"
#include <locale.h>

stJugador cargarUnJugador(int ultimoID) {
    stJugador aux;
    memset(&aux, 0, sizeof(stJugador)); // Inicializar para evitar basura

    aux.idJugador = ultimoID + 1;
    aux.ptsTotales = 0;
    aux.eliminado = 0;

    do {
        printf("Ingrese su nombre: ");
        fgets(aux.nombre, sizeof(aux.nombre), stdin);
        aux.nombre[strcspn(aux.nombre, "\n")] = '\0';
        printf("DEBUG: Nombre ingresado: '%s'\n", aux.nombre);
        if (strlen(aux.nombre) == 0 || !validarSoloLetras(aux.nombre)) {
            printf("❌ Nombre inválido. No puede estar vacío y debe contener solo letras.\n");
        }
    } while (strlen(aux.nombre) == 0 || !validarSoloLetras(aux.nombre));

    do {
        printf("Ingrese su apellido: ");
        fgets(aux.apellido, sizeof(aux.apellido), stdin);
        aux.apellido[strcspn(aux.apellido, "\n")] = '\0';
        printf("DEBUG: Apellido ingresado: '%s'\n", aux.apellido);
        if (strlen(aux.apellido) == 0 || !validarSoloLetras(aux.apellido)) {
            printf("❌ Apellido inválido. No puede estar vacío y debe contener solo letras.\n");
        }
    } while (strlen(aux.apellido) == 0 || !validarSoloLetras(aux.apellido));

    do {
        printf("Ingrese su email: ");
        fgets(aux.email, sizeof(aux.email), stdin);
        aux.email[strcspn(aux.email, "\n")] = '\0';
        printf("DEBUG: Email ingresado: '%s'\n", aux.email);
        if (!validarEmail(aux.email)) {
            printf("❌ Email inválido. Debe contener '@' y '.'.\n");
        }
    } while (!validarEmail(aux.email));

    do {
        printf("Ingrese su nombre de usuario: ");
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
        fgets(aux.password, sizeof(aux.password), stdin);
        aux.password[strcspn(aux.password, "\n")] = '\0';
        printf("DEBUG: Password ingresado: '%s'\n", aux.password);
        if (!validarPassword(aux.password)) {
            printf("❌ Contraseña inválida. Debe tener una mayúscula y una minúscula.\n");
        }
    } while (!validarPassword(aux.password));

    do {
        printf("Ingrese su DNI: ");
        fgets(aux.dni, sizeof(aux.dni), stdin);
        aux.dni[strcspn(aux.dni, "\n")] = '\0';
        printf("DEBUG: DNI ingresado: '%s'\n", aux.dni);
        if (!validarDNI(aux.dni)) {
            printf("❌ DNI inválido. Debe contener solo números y tener entre 7 y 9 dígitos.\n");
        }
    } while (!validarDNI(aux.dni));

    do {
        printf("Ingrese su nacionalidad o país: ");
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

int validarSoloLetras(char cadena[]) {
    int i = 0, valido = 1;
    while (cadena[i] != '\0' && valido) {
        if (!isalpha(cadena[i])) {
            valido = 0;
        }
        i++;
    }
    return valido;
}

int validarPassword(char clave[]) {
    int i = 0, tieneMayuscula = 0, tieneMinuscula = 0;
    while (clave[i] != '\0') {
        if (isupper(clave[i])) tieneMayuscula = 1;
        if (islower(clave[i])) tieneMinuscula = 1;
        i++;
    }
    return tieneMayuscula && tieneMinuscula;
}

int validarEmail(char correo[]) {
    int i = 0, tieneArroba = 0, tienePunto = 0;
    while (correo[i] != '\0') {
        if (correo[i] == '@') tieneArroba++;
        if (correo[i] == '.') tienePunto++;
        i++;
    }
    return tieneArroba == 1 && tienePunto >= 1;
}

int validarDNI(char dni[]) {
    int i = 0, valido = 1, longitud = strlen(dni);
    if (longitud < 7 || longitud > 9) {
        valido = 0;
    } else {
        while (dni[i] != '\0' && valido) {
            if (!isdigit(dni[i])) {
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
        cadena[i] = tolower(cadena[i]);
        i++;
    }
}

int obtenerUltimoID() {
    FILE *archivo = fopen(ARCHIVO_JUGADORES, "rb");
    stJugador aux;
    int ultimoID = 0;

    if (archivo) {
        fseek(archivo, 0, SEEK_END);
        long pos = ftell(archivo);
        if (pos > 0 && pos != -1) {
            fseek(archivo, pos - sizeof(stJugador), SEEK_SET);
            if (fread(&aux, sizeof(stJugador), 1, archivo) == 1) {
                ultimoID = aux.idJugador;
            }
        }
        fclose(archivo);
    }

    return ultimoID;
}

void guardarJugadorArchivo(stJugador jugador) {
    FILE *archivo = fopen(ARCHIVO_JUGADORES, "ab");
    if (archivo) {
        fwrite(&jugador, sizeof(stJugador), 1, archivo);
        fclose(archivo);
        printf("DEBUG: Jugador guardado - Username: '%s', Password: '%s'\n", jugador.username, jugador.password);
    } else {
        printf("Error al abrir el archivo %s.\n", ARCHIVO_JUGADORES);
    }
}

int existeUsernameEnArchivo(char username[]) {
    FILE *archivo = fopen(ARCHIVO_JUGADORES, "rb");
    stJugador aux;
    int existe = 0;

    if (archivo) {
        while (fread(&aux, sizeof(stJugador), 1, archivo)) {
            if (strcasecmp(aux.username, username) == 0 && !aux.eliminado) {
                existe = 1;
                break;
            }
        }
        fclose(archivo);
    }

    return existe;
}

void imprimirJugadoresArchivo() {
    FILE *arch = fopen(ARCHIVO_JUGADORES, "rb");
    if (arch) {
        stJugador aux;
        printf("\n--- Contenido de jugadores.dat ---\n");
        while (fread(&aux, sizeof(stJugador), 1, arch)) {
            if (!aux.eliminado) {
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
        }
        fclose(arch);
    } else {
        printf("Error al abrir %s para depuración.\n", ARCHIVO_JUGADORES);
    }
}
