#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

typedef struct {
    int idJugador;
    char nombre[30];
    char apellido[30];
    char email[50];
    char username[30];
    char password[20];
    char dni[10];
    int ptsTotales;
    int eliminado; // 0 = activo, 1 = eliminado
    char pais[30]; // campo agregado
} stJugador;


#endif // JUGADOR_H_INCLUDED
