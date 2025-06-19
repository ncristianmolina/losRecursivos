#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jugador.h"
#include "registro.h" // o el header correspondiente
#include "tateti.h"
#include <locale.h>

// Función principal del juego. Controla la partida.
void jugar(int contraBot) {
    char tablero[3][3];
    char jugador = JUGADOR1;
    int juegoTerminado = 0;

    inicializarTablero(tablero);

    while (!juegoTerminado) {
        mostrarTablero(tablero);
        pedirMovimiento(tablero, jugador, contraBot);

        if (hayGanador(tablero, jugador)) {
            mostrarTablero(tablero);
            printf("¡Jugador %c ha ganado!\n", jugador);
            juegoTerminado = 1;
        } else if (tableroLleno(tablero)) {
            mostrarTablero(tablero);
            printf("¡Empate!\n");
            juegoTerminado = 1;
        } else {
            // Cambia de jugador
            if (jugador == JUGADOR1) {
                  jugador = JUGADOR2;
            } else {
                 jugador = JUGADOR1;
                  }
        }
    }
}

// Inicializa el tablero con los números del 1 al 9 como caracteres
void inicializarTablero(char tablero[3][3]) {
    char num = '1';
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tablero[i][j] = num++;
}

// Muestra el estado actual del tablero
void mostrarTablero(char tablero[3][3]) {
    system("cls");
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", tablero[i][0], tablero[i][1], tablero[i][2]);
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}




// Pide al jugador que ingrese una jugada, o elige automáticamente si es el bot
void pedirMovimiento(char tablero[3][3], char jugador, int contraBot) {
    int fila, col;
    char input;

    if (contraBot && jugador == JUGADOR2) {
        int num;
        do {
            num = (rand() % 9) + 1;
            numeroACoordenadas(num, &fila, &col);
        } while (!esMovimientoValido(tablero, fila, col));
        printf("Bot elige la casilla %d\n", num);
        tablero[fila][col] = jugador;
    } else {
        do {
            printf("Jugador %c, elija una casilla (1-9): ", jugador);
            scanf(" %c", &input);

            if (input >= '1' && input <= '9') {
                numeroACoordenadas(input - '1' + 1, &fila, &col);
            } else {
                printf("Entrada inválida. Solo se permiten números del 1 al 9.\n");
                continue;
            }

        } while (!(input >= '1' && input <= '9') || !esMovimientoValido(tablero, fila, col));

        tablero[fila][col] = jugador;
    }
}

// Convierte un número del 1 al 9 en coordenadas fila y columna del tablero
void numeroACoordenadas(int num, int *fila, int *col) {
    int indice = num - 1;
    *fila = indice / 3;
    *col = indice % 3;
}
// Verifica si el casillero no está ocupado por un jugador
int esMovimientoValido(char tablero[3][3], int fila, int col) {
    int valido = 0;
    if (tablero[fila][col] != JUGADOR1 && tablero[fila][col] != JUGADOR2) {
        valido = 1;
    }
    return valido;
}

// Determina si un jugador ha ganado
int hayGanador(char tablero[3][3], char jugador) {
    int gano = 0;

    // Verifica filas y columnas
    for (int i = 0; i < 3; i++) {
        if ((tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador) ||
            (tablero[0][i] == jugador && tablero[1][i] == jugador && tablero[2][i] == jugador)) {
            gano = 1;
        }
    }

    // Verifica diagonales
    if ((tablero[0][0] == jugador && tablero[1][1] == jugador && tablero[2][2] == jugador) ||
        (tablero[0][2] == jugador && tablero[1][1] == jugador && tablero[2][0] == jugador)) {
        gano = 1;
    }

    return gano;
}


// Verifica si todas las casillas del tablero están ocupadas
int tableroLleno(char tablero[3][3]) {
    int lleno = 1;  // Asumimos que está lleno

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] != JUGADOR1 && tablero[i][j] != JUGADOR2) {
                lleno = 0;  // Si hay una casilla vacía, no está lleno
            }
        }
    }

    return lleno;
}
