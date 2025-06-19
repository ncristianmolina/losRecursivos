#ifndef INICIO_SESION_H_INCLUDED
#define INICIO_SESION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jugador.h"  // ✅ Ya incluye la estructura

/// FUNCIONES CON VALIDACIONES
int validarSoloLetras(char cadena[]);
int validarPassword(char clave[]);
int validarEmail(char correo[]);
int validarDNI(char dni[]);
void convertirMinusculas(char cadena[]);

/// ARCHIVO
int obtenerUltimoID();
void guardarJugadorArchivo(stJugador jugador);

#endif // INICIO_SESION_H_INCLUDED
