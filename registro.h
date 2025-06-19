#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tateti.h"
#include "jugador.h"  // ✅ Se importa la estructura desde aquí

#define MAX_JUGADORES 100
#define ARCHIVO_JUGADORES "jugadores.dat"

// Registro
stJugador cargarUnJugador(int ultimoID);
int validarSoloLetras(char cadena[]);
int validarPassword(char clave[]);
int validarEmail(char correo[]);
int validarDNI(char dni[]);
void convertirMinusculas(char cadena[]);
int obtenerUltimoID();
void guardarJugadorArchivo(stJugador jugador);
int existeUsernameEnArchivo(char username[]);


// Login
int loginJugador(stJugador* jugadorLogueado);
void menuPostLogin(stJugador jugadorLogueado);
void jugarContraMaquina(stJugador* jugador);
void jugarContraJugador(stJugador* jugador);
void eliminarCuenta(stJugador* jugador);
void guardarCambiosJugador(stJugador jugadorActualizado);

#endif // REGISTRO_H_INCLUDED
