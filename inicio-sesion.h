#ifndef INICIO_SESION_H_INCLUDED
#define INICIO_SESION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jugador.h"

int loginJugador(stJugador* jugadorLogueado);
void jugarContraMaquina(stJugador* jugador);
void jugarContraJugador(stJugador* jugador);
void eliminarCuenta(stJugador* jugador);
void guardarCambiosJugador(stJugador jugadorActualizado);
void cambiarUsername(stJugador* jugador);

#endif // INICIO_SESION_H_INCLUDED
