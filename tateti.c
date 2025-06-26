#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "tateti.h"

#define SIZE 3

/* Hecho por Cristian. Gestiona partida y determina ganador. */
int jugar(int contraBot, int dificultad) {
    char tablero[3][3];
    char jugador = JUGADOR1;
    int juegoTerminado = 0;

    inicializarTablero(tablero);

    if (contraBot) {
        printf("\nSeleccione dificultad:\n1. Fácil\n2. Difícil\nOpción: ");
        scanf("%d", &dificultad);
        while (getchar() != '\n'); // Limpiar búfer en lugar de fflush(stdin)
        if (dificultad != 1 && dificultad != 2) {
            dificultad = 1; // Por defecto, fácil
        }
    }

    while (!juegoTerminado) {
        mostrarTablero(tablero);
        pedirMovimiento(tablero, jugador, contraBot, dificultad);

        if (hayGanador(tablero, jugador)) {
            mostrarTablero(tablero);
            printf("¡Jugador %c ha ganado!\n", jugador);
            juegoTerminado = 1;
            return (jugador == JUGADOR1) ? 1 : 2; // 1 si gana Jugador 1, 2 si gana Jugador 2
        } else if (tableroLleno(tablero)) {
            mostrarTablero(tablero);
            printf("¡Empate!\n");
            juegoTerminado = 1;
            return 0; // Empate
        } else {
            jugador = (jugador == JUGADOR1) ? JUGADOR2 : JUGADOR1;
        }
    }

    return 0; // Por completitud, aunque no debería llegar aquí
}

/* Hecha por Luciana. Inicializa tablero con números. */
void inicializarTablero(char tablero[3][3]) {
    char num = '1';
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tablero[i][j] = num++;
}

/* Hecha por Luciana. Muestra tablero en pantalla. */
void mostrarTablero(char tablero[3][3]) {
    system("cls");
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", tablero[i][0], tablero[i][1], tablero[i][2]);
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}

/* Hecho por Cristian. Verifica validez movimiento tablero. */
int esMovimientoValido(char tablero[3][3], int fila, int col) {
    return tablero[fila][col] != JUGADOR1 && tablero[fila][col] != JUGADOR2;
}

/* Hecho por Cristian. Solicita y aplica movimiento jugador. */
void pedirMovimiento(char tablero[3][3], char jugador, int contraBot, int dificultad) {
    int fila, col;
    char input;

    if (contraBot && jugador == JUGADOR2) {
        int casilla;
        if (dificultad == 2) {
            casilla = dificultadDificil(tablero, jugador);
        } else {
            casilla = casillaRandom(tablero, jugador);
        }
        numeroACoordenadas(casilla, &fila, &col);
        printf("Bot elige la casilla %d\n", casilla);
        tablero[fila][col] = jugador;
    } else {
        do {
            printf("Jugador %c, elija una casilla (1-9): ", jugador);
            scanf(" %c", &input);
            while (getchar() != '\n'); // Limpiar búfer
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

/* Hecho por Luciana. Convierte número a coordenadas. */
void numeroACoordenadas(int num, int *fila, int *col) {
    int indice = num - 1;
    *fila = indice / 3;
    *col = indice % 3;
}

/* Hecho por Cristian. Verifica si hay ganador tablero. */
int hayGanador(char tablero[3][3], char jugador) {
    for (int i = 0; i < 3; i++) {
        if ((tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador) ||
            (tablero[0][i] == jugador && tablero[1][i] == jugador && tablero[2][i] == jugador))
            return 1;
    }
    if ((tablero[0][0] == jugador && tablero[1][1] == jugador && tablero[2][2] == jugador) ||
        (tablero[0][2] == jugador && tablero[1][1] == jugador && tablero[2][0] == jugador))
        return 1;

    return 0;
}

/* Hecho por Cristian. Verifica si tablero está lleno. */
int tableroLleno(char tablero[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tablero[i][j] != JUGADOR1 && tablero[i][j] != JUGADOR2)
                return 0;
    return 1;
}

/* Hecho por Cristian. Selecciona casilla aleatoria válida. */
int casillaRandom(char tablero[3][3], char jugador) {
    int fila, col, casilla;
    do {
        casilla = (rand() % 9) + 1;
        numeroACoordenadas(casilla, &fila, &col);
    } while (!esMovimientoValido(tablero, fila, col));
    return casilla;
}

/* Hecho por Cristian y Luciana. Calcula movimiento difícil bot. */
int dificultadDificil(char tablero[3][3], char jugador) {
    int fila, col;
    char oponente = (jugador == JUGADOR1) ? JUGADOR2 : JUGADOR1;

    // Intentar ganar
    for (int i = 1; i <= 9; i++) {
        numeroACoordenadas(i, &fila, &col);
        if (esMovimientoValido(tablero, fila, col)) {
            char temp = tablero[fila][col];
            tablero[fila][col] = jugador;
            if (hayGanador(tablero, jugador)) {
                tablero[fila][col] = temp;
                return i;
            }
            tablero[fila][col] = temp;
        }
    }

    // Bloquear oponente
    for (int i = 1; i <= 9; i++) {
        numeroACoordenadas(i, &fila, &col);
        if (esMovimientoValido(tablero, fila, col)) {
            char temp = tablero[fila][col];
            tablero[fila][col] = oponente;
            if (hayGanador(tablero, oponente)) {
                tablero[fila][col] = temp;
                return i;
            }
            tablero[fila][col] = temp;
        }
    }

    // Centro
    if (tablero[1][1] != JUGADOR1 && tablero[1][1] != JUGADOR2)
        return 5;

    // Esquinas
    int esquinas[] = {1, 3, 7, 9};
    for (int i = 0; i < 4; i++) {
        numeroACoordenadas(esquinas[i], &fila, &col);
        if (esMovimientoValido(tablero, fila, col))
            return esquinas[i];
    }

    // Aleatorio
    return casillaRandom(tablero, jugador);
}
