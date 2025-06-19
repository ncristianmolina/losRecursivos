#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"
#include "jugador.h"
#include <locale.h>

// ========== FUNCIÓN DE REGISTRO ==========
stJugador cargarUnJugador(int ultimoID)
{
    stJugador aux;

    aux.idJugador = ultimoID + 1;
    aux.ptsTotales = 0;
    aux.eliminado = 0;

    // Nombre
    do
    {
        printf("Ingrese su nombre: ");
        fflush(stdin);
        gets(aux.nombre);

        if (strlen(aux.nombre) == 0 || !validarSoloLetras(aux.nombre))
        {
            printf("❌ Nombre inválido. No puede estar vacío y debe contener solo letras.\n");
        }

    }
    while (strlen(aux.nombre) == 0 || !validarSoloLetras(aux.nombre));

    // Apellido
    do
    {
        printf("Ingrese su apellido: ");
        fflush(stdin);
        gets(aux.apellido);

        if (strlen(aux.apellido) == 0 || !validarSoloLetras(aux.apellido))
        {
            printf("❌ Apellido inválido. No puede estar vacío y debe contener solo letras.\n");
        }

    }
    while (strlen(aux.apellido) == 0 || !validarSoloLetras(aux.apellido));

    // Email
    do
    {
        printf("Ingrese su email: ");
        fflush(stdin);
        gets(aux.email);

        if (!validarEmail(aux.email))
        {
            printf("❌ Email inválido. Debe contener '@' y '.'.\n");
        }

    }
    while (!validarEmail(aux.email));

    // Username
    // Username
    do
    {
        printf("Ingrese su nombre de usuario: ");
        fflush(stdin);
        gets(aux.username);
        convertirMinusculas(aux.username);

        if (!validarSoloLetras(aux.username))
        {
            printf("❌ Usuario inválido. Solo debe contener letras.\n");
        }
        else if (existeUsernameEnArchivo(aux.username))
        {
            printf("❌ Ese nombre de usuario ya está registrado. Elija otro.\n");
        }

    }
    while (!validarSoloLetras(aux.username) || existeUsernameEnArchivo(aux.username));


    // Contraseña
    do
    {
        printf("Ingrese su contraseña (mínimo una mayúscula y una minúscula): ");
        fflush(stdin);
        gets(aux.password);

        if (!validarPassword(aux.password))
        {
            printf("❌ Contraseña inválida. Debe tener una mayúscula y una minúscula.\n");
        }

    }
    while (!validarPassword(aux.password));

    // DNI
    do
    {
        printf("Ingrese su DNI: ");
        fflush(stdin);
        gets(aux.dni);

        if (!validarDNI(aux.dni))
        {
            printf("❌ DNI inválido. Debe contener solo números y tener entre 7 y 9 dígitos.\n");
        }

    }
    while (!validarDNI(aux.dni));

    printf("\n✅ ¡Registro completado con éxito!\n");
    system("pause");
    system("cls");

    return aux;
}

// ========== FUNCIONES DE VALIDACIÓN ==========

int validarSoloLetras(char cadena[])
{
    int i = 0, valido = 1;
    while (cadena[i] != '\0' && valido == 1)
    {
        if (!((cadena[i] >= 65 && cadena[i] <= 90) || (cadena[i] >= 97 && cadena[i] <= 122)))
        {
            valido = 0;
        }
        i++;
    }
    return valido;
}

int validarPassword(char clave[])
{
    int i = 0, tieneMayuscula = 0, tieneMinuscula = 0, valido = 0;
    while (clave[i] != '\0')
    {
        if (clave[i] >= 65 && clave[i] <= 90) tieneMayuscula = 1;
        if (clave[i] >= 97 && clave[i] <= 122) tieneMinuscula = 1;
        i++;
    }
    if (tieneMayuscula && tieneMinuscula) valido = 1;
    return valido;
}

int validarEmail(char correo[])
{
    int i = 0, tieneArroba = 0, tienePunto = 0, valido = 0;
    while (correo[i] != '\0')
    {
        if (correo[i] == '@') tieneArroba = 1;
        if (correo[i] == '.') tienePunto = 1;
        i++;
    }
    if (tieneArroba && tienePunto) valido = 1;
    return valido;
}

int validarDNI(char dni[])
{
    int i = 0, valido = 1, longitud = strlen(dni);
    if (longitud < 7 || longitud > 9)
    {
        valido = 0;
    }
    else
    {
        while (dni[i] != '\0' && valido == 1)
        {
            if (!(dni[i] >= 48 && dni[i] <= 57))
            {
                valido = 0;
            }
            i++;
        }
    }
    return valido;
}

void convertirMinusculas(char cadena[])
{
    int i = 0;
    while (cadena[i] != '\0')
    {
        if (cadena[i] >= 65 && cadena[i] <= 90)
        {
            cadena[i] += 32;
        }
        i++;
    }
}

// ========== FUNCIONES DE ARCHIVO ==========

int obtenerUltimoID()
{
    FILE* archivo = fopen("jugadores.dat", "rb");
    stJugador aux;
    int ultimoID = 0;

    if (archivo != NULL)
    {
        fseek(archivo, 0, SEEK_END);
        int totalJugadores = ftell(archivo) / sizeof(stJugador);
        if (totalJugadores > 0)
        {
            fseek(archivo, -1 * sizeof(stJugador), SEEK_END);
            fread(&aux, sizeof(stJugador), 1, archivo);
            ultimoID = aux.idJugador;
        }
        fclose(archivo);
    }

    return ultimoID;
}

void guardarJugadorArchivo(stJugador jugador)
{
    FILE* archivo = fopen("jugadores.dat", "ab");
    if (archivo != NULL)
    {
        fwrite(&jugador, sizeof(stJugador), 1, archivo);
        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
}

int existeUsernameEnArchivo(char username[])
{
    FILE* archivo = fopen(ARCHIVO_JUGADORES, "rb");
    stJugador aux;
    int existe = 0;

    if (archivo != NULL)
    {
        while (fread(&aux, sizeof(stJugador), 1, archivo) > 0)
        {
            if (strcmpi(aux.username, username) == 0 && aux.eliminado == 0)
            {
                existe = 1;
                break;
            }
        }
        fclose(archivo);
    }

    return existe;
}

