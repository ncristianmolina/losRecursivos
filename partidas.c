#include <stdio.h>
#include <stdlib.h>
#include "inicio-sesion.h"
#include "registro.h"
#include "tateti.h"
#include "jugador.h"
#include "mock.h"
#include "partidas.h"
#include <locale.h>

#define AR_PARTIDAS "partidas.dat"

#define GANADOR 1
#define EMPATE 2
#define PERDEDOR 0

/** Hecha por Luciana. Obtiene �ltimo id de la partida**/
int obtenerUltimoIDPartida() {
    FILE *archi = fopen("partidas.dat", "rb");
    int ultimoID = 0;

    if (archi) {
        stPartida partida;


        while (fread(&partida, sizeof(stPartida), 1, archi) == 1) {
            if (partida.idPartida > ultimoID) {
                ultimoID = partida.idPartida;
            }
        }
        fclose(archi);
    }

    return ultimoID;
}



/**Hecha por Luciana. Muestra partidas**/

void imprimirPartidas(stPartida partida)
  {
        printf("ID Partida: %d\n", partida.idPartida);
        printf("Dificultad: %s\n", partida.dificultad);
        printf("Es contra CPU: %s\n", partida.esContraCpu ? "S�" : "No");
        printf("----------------------------------------\n");
   }


/**Hecha por Luciana. Genera partidas de manera aleatoria**/
void generarPartidaAleatoria(stPartida *partida, int idPartida)
{
   const char *dificultad[] = { "Aprendiz", "Terrorista"};
   const char *esContraCpu[] = { "No", "S�"};

    partida->idPartida = idPartida;
    strcpy(partida->dificultad, dificultad[rand() % 2]);
    partida->esContraCpu = rand() %2 ;


}

/**Hecha por Luciana. Guarda partidas en archivo**/
 void guardarPartidasEnArchivo(const char *nombreArchivo, stPartida *partida, int cantidad) {
    FILE *archi = fopen(nombreArchivo, "ab");
    if (archi) {
        fwrite(partida, sizeof(stPartida), cantidad, archi);
        fclose(archi);
    }
    printf("Se guardaron %d partidas en el archivo.\n", cantidad);

}

/**Hecha por Luciana. Permite visualizar las partidas en el archivo**/
void leerPartidasDesdeArchivo(const char *nombreArchivo) {
    FILE *archi = fopen(nombreArchivo, "rb");
    if (archi) {
        stPartida partida;
        printf("\n--- Partidas guardados ---\n");
        while (fread(&partida, sizeof(stPartida), 1, archi) == 1) {
            imprimirPartidas(partida);
        }
        fclose(archi);
    }
}

/**Hecha por Luciana calcula resultado**/
int calcularPuntos(int resultado) {
    if (resultado == GANADOR) return 3;
    else if (resultado == EMPATE) return 1;
    else return 0;
}

/**Hecha por Luciana. Genera y guarda partidas seg�n cantidad indicada**/
void generarYGuardarPartidas(int cantidad) {
    stPartida p;
    int ultimoID = obtenerUltimoIDPartida();

    for (int i = 0; i < cantidad; i++) {
        int nuevoID = ultimoID + i + 1;
        generarPartidaAleatoria(&p, nuevoID);
        guardarPartidasEnArchivo(AR_PARTIDAS, &p, 1);
    }
}




