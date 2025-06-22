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

void imprimirPartidas(stPartida partida)
  {
        printf("ID Partida: %d\n", partida.idPartida);
        printf("Dificultad: %s\n", partida.dificultad);
        printf("Es contra CPU: %s\n", partida.esContraCpu ? "Sí" : "No");
        printf("----------------------------------------\n");
   }



void generarPartidaAleatoria(stPartida *partida, int idPartida)
{
   const char *dificultad[] = { "Aprendiz", "Terrorista"};
   const char *esContraCpu[] = { "No", "Sí"};

    partida->idPartida = idPartida;
    strcpy(partida->dificultad, dificultad[rand() % 2]);
    partida->esContraCpu = rand() %2 ;


}


 void guardarPartidasEnArchivo(const char *nombreArchivo, stPartida *partida, int cantidad) {
    FILE *archi = fopen(nombreArchivo, "ab");
    if (archi) {
        fwrite(partida, sizeof(stPartida), cantidad, archi);
        fclose(archi);
        printf("Se guardaron %d partidas en el archivo binario.\n", cantidad);
    }


}


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
