#ifndef PARTIDAS_H_INCLUDED
#define PARTIDAS_H_INCLUDED

typedef struct {
    int idPartida;
    char dificultad [15]; /// 0 = aprendiz- 1 = terrorista
    int esContraCpu; /// 0 No - 1 Sí
} stPartida;



 void imprimirPartidas(stPartida partida);
 void generarPartidaAleatoria(stPartida *partida, int idPartida);
 void guardarPartidasEnArchivo(const char *nombreArchivo, stPartida *partida, int cantidad);
 void leerPartidasDesdeArchivo(const char *nombreArchivo) ;


#endif // PARTIDAS_H_INCLUDED
