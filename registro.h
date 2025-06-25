#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tateti.h"
#include "jugador.h"

#define MAX_JUGADORES 100
#define ARCHIVO_JUGADORES "jugadores.dat"

stJugador cargarUnJugador(int ultimoID);
int validarSoloLetras(char cadena[]);
int validarPassword(char clave[]);
int validarEmail(char correo[]);
int validarDNI(char dni[]);
void convertirMinusculas(char cadena[]);
int obtenerUltimoID();
void guardarJugadorArchivo(stJugador jugador);
int existeUsernameEnArchivo(char username[]);
void imprimirJugadoresArchivo();

#endif // REGISTRO_H_INCLUDED
