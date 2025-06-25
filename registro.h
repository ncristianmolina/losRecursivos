#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED
#include "jugador.h"

#define ARCHIVO_JUGADORES "jugadores.dat"

int obtenerUltimoID();
stJugador cargarUnJugador(int id);
void guardarJugadorArchivo(stJugador j);
void imprimirJugadoresArchivo();
int validarSoloLetras(char cadena[]);
int validarPassword(char clave[]);
int validarEmail(char correo[]);
int validarDNI(char dni[]);
void convertirMinusculas(char cadena[]);
int existeUsernameEnArchivo(char username[]);

#endif // REGISTRO_H_INCLUDED
