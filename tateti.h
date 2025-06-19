#ifndef TATETI_H_INCLUDED
#define TATETI_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define JUGADOR1 'X'
#define JUGADOR2 'O'

void numeroACoordenadas(int num, int *fila, int *col);
void inicializarTablero(char tablero[3][3]);
void mostrarTablero(char tablero[3][3]);
int esMovimientoValido(char tablero[3][3], int fila, int col);
void pedirMovimiento(char tablero[3][3], char jugador, int contraBot);
int hayGanador(char tablero[3][3], char jugador);
int tableroLleno(char tablero[3][3]);
void jugar(int contraBot);

#endif // TATETI_H_INCLUDED
