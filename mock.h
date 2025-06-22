#ifndef MOCK_H_INCLUDED
#define MOCK_H_INCLUDED


#define NUM_JUGADORES_ALEATORIOS 2000
#define NUM_JUGADORES_CARGADOS 0
#define TOTAL_JUGADORES (NUM_JUGADORES_CARGADOS + NUM_JUGADORES_ALEATORIOS)
#define jugadoresPrecargados[NUM_JUGADORES_PRECARGADOS];

#define AR_JUGADORES "jugadores.dat"



typedef struct {
    int idJugador;
    char nombre[30];
    char apellido[30];
    char email[50];
    char username[30];
    char password[20];
    char DNI [10];
    int ptsTotales;
    int eliminado; /// puede ser 0 = activo, 1 = eliminado
    char pais[30];
} stJugador;

void generarContrasena(char *destino, int longitud);
void imprimirJugador(stJugador);
void generarJugadorAleatorio(stJugador *jugador, int idJugador);
void guardarJugadoresEnArchivoBinario(const char *nombreArchivo, stJugador *jugadores, int cantidad);
void leerJugadoresDesdeArchivo(const char *nombreArchivo);
void leerJugadoresDesdeArchivo(const char *nombreArchivo);



#endif // MOCK_H_INCLUDED
