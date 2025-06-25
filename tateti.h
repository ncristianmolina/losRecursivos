#ifndef TATETI_H_INCLUDED
#define TATETI_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define JUGADOR1 'X'
#define JUGADOR2 'O'

// Declaraciones de funciones
void numeroACoordenadas(int num, int *fila, int *col);
void inicializarTablero(char tablero[3][3]);
void mostrarTablero(char tablero[3][3]);
int esMovimientoValido(char tablero[3][3], int fila, int col);
void pedirMovimiento(char tablero[3][3], char jugador, int contraBot, int dificultad);
int hayGanador(char tablero[3][3], char jugador);
int tableroLleno(char tablero[3][3]);
int jugar(int contraBot, int dificultad);
int casillaRandom(char tablero[3][3], char jugador);
int dificultadDificil(char tablero[3][3], char jugador);

#endif // TATETI_H_INCLUDED
