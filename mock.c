#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "mock.h"
#include "jugador.h"

#define AR_JUGADORES "jugadores.dat"


/**Hecha por Luciana- genera contraseñas utilizando hasta caracteres especiales**/
void generarContrasena(char *destino, int longitud) {
    const char *caracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()-_=+[]{};:,.<>?";
    int largo = strlen(caracteres);
    for (int i = 0; i < longitud - 1; i++) {
        destino[i] = caracteres[rand() % largo];
    }
    destino[longitud - 1] = '\0';
}

/**Hecha por Luciana- Muestra un jugador**/

void imprimirJugador(stJugador jugador) {
    if (jugador.eliminado == 0) {
        printf("ID Jugador: %d\n", jugador.idJugador);
        printf("Nombre: %s\n", jugador.nombre);
        printf("Apellido: %s\n", jugador.apellido);
        printf("Email: %s\n", jugador.email);
        printf("Nombre de usuario: %s\n", jugador.username);
        printf("Contraseña: %s\n", jugador.password);
        printf("DNI: %s\n", jugador.dni);
        printf("Puntaje: %d\n", jugador.ptsTotales);
        printf("Nacionalidad: %s\n", jugador.pais);
        printf("----------------------------------------\n");
    }
}

/** Hecha por Luciana. genera jugadores de manera aleatoria
Nombres-Apellidos-países-mails-nicknames-contraseñas y dni**/

void generarJugadorAleatorio(stJugador *jugador, int idJugador) {
    const char *nombres[] = {"Juan", "Ana", "Luis", "Maria", "Pedro", "Laura", "Mariano", "Sofia", "Valentina",
                             "Mateo", "Camila", "Facundo", "Lucia", "Diego", "Abril", "Ignacio", "Catalina", "Lucas",
                             "Martina", "Agustin", "Victoria", "Tomas", "Florencia", "Santiago", "Belen", "Matias",
                             "Julieta", "Nicolas", "Joaquin", "Gonzalo", "Rocio", "Micaela", "Luciana", "German"};
    const char *apellidos[] = {"Perez", "Garcia", "Martinez", "Lopez", "Gonzalez", "Sanchez", "Messi", "Rodriguez",
                               "Fernandez", "Gallardo", "Gomez", "Diaz", "Romero", "Aimar", "Torres", "Alvarez",
                               "Ruiz", "Ramirez", "Gutierrez", "Morales", "Navarro", "Castro", "Rios", "Silva",
                               "Mendoza", "Ortiz", "Francescoli", "Maidana", "Acosta"};
    const char *paises[] = {"Afganistán", "Albania", "Alemania", "Andorra", "Angola", "Antigua y Barbuda",
                            "Arabia Saudita", "Argelia", "Argentina", "Armenia", "Australia", "Austria",
                            "Azerbaiyán", "Bahamas", "Bangladesh", "Bahrein", "Barbados", "Bélgica",
                            "Belice", "Benín", "Bielorrusia", "Birmania", "Bolivia", "Bosnia y Herzegovina",
                            "Botswana", "Brasil", "Brunéi", "Bulgaria", "Burkina Faso", "Burundi",
                            "Bhutan", "Cabo Verde", "Camboya", "Camerún", "Canadá", "Catar",
                            "Chad", "Chile", "China", "Chipre", "Ciudad del Vaticano", "Colombia",
                            "Comores", "Corea del Norte", "Corea del Sur", "Costa de Marfil", "Costa Rica",
                            "Croacia", "Cuba", "Dinamarca", "Dominica", "Ecuador", "Egipto",
                            "El Salvador", "Emiratos Árabes Unidos", "Eritrea", "Eslovaquia", "Eslovenia",
                            "España", "Estados Unidos", "Estonia", "Swazilandia", "Etiopía", "Filipinas",
                            "Finlandia", "Fiji", "Francia", "Gabón", "Gambia", "Georgia", "Ghana",
                            "Granada", "Grecia", "Guatemala", "Guinea", "Guinea-Bisseau", "Guinea Ecuatorial",
                            "Guyana", "Haití", "Honduras", "Hungría", "India", "Indonesia", "Irak", "Irán",
                            "Irlanda", "Islandia", "Islas Marshall", "Islas Salomón", "Palestina", "Italia",
                            "Jamaica", "Japón", "Jordania", "Kazajistán", "Kenia", "Kirguistán", "Kiribati",
                            "Kuwait", "Laos", "Lesoto", "Letonia", "Líbano", "Liberia", "Libia",
                            "Liechtenstein", "Lituania", "Luxemburgo", "Madagascar", "Malasia", "Malawi",
                            "Maldivas", "Malí", "Malta", "Marruecos", "Mauricio", "Mauritania", "México",
                            "Micronesia", "Moldavia", "Mónaco", "Mongolia", "Montenegro", "Mozambique",
                            "Namibia", "Nauru", "Nepal", "Nicaragua", "Níger", "Nigeria", "Noruega",
                            "Nueva Zelanda", "Omán", "Países Bajos", "Pakistán", "Palaos", "Panamá",
                            "Papúa Nueva Guinea", "Paraguay", "Perú", "Polonia", "Portugal", "Reino Unido",
                            "República Centroafricana", "República Checa", "República del Congo",
                            "República Democrática del Congo", "República Dominicana", "Rwanda",
                            "Rumania", "Rusia", "Samoa", "San Cristóbal y Nieves", "San Marino",
                            "San Vicente y las Granadinas", "Santa Lucía", "Santo Tomé y Príncipe",
                            "Senegal", "Serbia", "Seychelles", "Sierra Leona", "Singapur", "Siria",
                            "Somalia", "Sri Lanka", "Sudáfrica", "Sudán", "Sudán del Sur", "Suecia",
                            "Suiza", "Surinam", "Tailandia", "Tanzania", "Tayikistán", "Timor Oriental",
                            "Togo", "Tonga", "Trinidad y Tobago", "Túnez", "Turkmenistán", "Turquía",
                            "Tuvalu", "Ucrania", "Uganda", "Uruguay", "Uzbekistán", "Vanuatu",
                            "Venezuela", "Vietnam", "Yemen", "Djibuti", "Zambia", "Zimbabwe", "Kosovo"};
    const char *dominios[] = {"@gmail.com", "@hotmail.com", "@live.com", "@outlook.com", "@yahoo.com"};
    const char *objetos[] = {"luna", "sol", "estrella", "rayo", "fuego", "nube", "cielo", "mar", "roca", "bosque",
                             "cometa", "pistola", "bomba", "torpedo", "tortuga", "perro", "gato", "pelota",
                             "zapallo", "banana", "chorlito", "chicharra", "picodulce", "tomate", "mojarrita",
                             "pescado", "lanzajabalina", "Mastantuono", "Dracula", "palta"};
    const char *adjetivos[] = {"brillante", "oscuro", "rapido", "misterioso", "feliz", "triste", "rojo", "azul",
                               "salvaje", "suave", "veloz", "letal", "atomica", "zuripante", "millonario", "crack",
                               "molina", "mojada", "picante", "soberbia", "inofensivo", "chillon", "muda",
                               "picarona", "jugueton", "mimoso", "rabioso", "precoz", "mercenario", "chupasangre",
                               "jugosa"};

    jugador->idJugador = idJugador;
    strcpy(jugador->nombre, nombres[rand() % (sizeof(nombres) / sizeof(nombres[0]))]);
    strcpy(jugador->apellido, apellidos[rand() % (sizeof(apellidos) / sizeof(apellidos[0]))]);
    sprintf(jugador->email, "%s.%s%s", jugador->nombre, jugador->apellido, dominios[rand() % (sizeof(dominios) / sizeof(dominios[0]))]);
    sprintf(jugador->username, "%s_%s_%d", objetos[rand() % (sizeof(objetos) / sizeof(objetos[0]))], adjetivos[rand() % (sizeof(adjetivos) / sizeof(adjetivos[0]))], rand() % 10000);
    generarContrasena(jugador->password, 12);
    sprintf(jugador->dni, "%08d", (rand() % 35000001) + 20000000); // Generar DNIs entre 20,000,000 y 55,000,000
    jugador->ptsTotales = rand() % 100000;
    strcpy(jugador->pais, paises[rand() % (sizeof(paises) / sizeof(paises[0]))]);
    jugador->eliminado = 0;
}
/**Hecha por Luciana: permite indicar la cantidad de registros de jugadores a generar. De esta manera, no se corrompe el archivo**/
void generarYGuardarJugadores(int cantidad) {
    stJugador j;
    for (int i = 0; i < cantidad; i++) {
        int nuevoID = obtenerUltimoIDPlayer() + 1;
        generarJugadorAleatorio(&j, nuevoID);
        guardaJugadorArchivo(j);
    }
    printf("Se generaron y guardaron %d jugadores.\n", cantidad);
}
/**Hecha por Luciana: guarda a jugadores en un archivo**/

void guardarJugadoresEnArchivo(const char *nombreArchivo, stJugador *jugadores, int cantidad) {
    FILE *archi = fopen(nombreArchivo, "ab");
    if (archi) {
        fwrite(jugadores, sizeof(stJugador), cantidad, archi);
        fclose(archi);
        printf("Se guardaron %d jugadores en el archivo\n", cantidad);
    }
}


/**Hecha por Luciana: visualiza los registros de los jugadores en el archivo**/
void leerJugadoresDesdeArchivo(const char *nombreArchivo) {
    FILE *archi = fopen(nombreArchivo, "rb");
    if (archi) {
        stJugador jugador;
        printf("\n--- Jugadores guardados ---\n");
        while (fread(&jugador, sizeof(stJugador), 1, archi) == 1) {
            imprimirJugador(jugador);
        }
        fclose(archi);
    }
}

/** Hecha por Luciana: ID auto-incremental **/

int obtenerUltimoIDPlayer() {
    FILE *archi = fopen(AR_JUGADORES, "rb");
    stJugador aux;
    int id = 0;

    if (archi) {
        while (fread(&aux, sizeof(stJugador), 1, archi)) {
            if (aux.idJugador > id) id = aux.idJugador;
        }
        fclose(archi);
    }

    return id;
}

/** Hecha por Luciana. Actualiza registro de jugador en archivo**/
void actualizarJugadorEnArchivo(stJugador jugador) {
    FILE *archi = fopen(AR_JUGADORES, "r+b");
    if (archi) {
        stJugador aux;
        while (fread(&aux, sizeof(stJugador), 1, archi)) {
            if (aux.idJugador == jugador.idJugador) {
                long pos = ftell(archi) - sizeof(stJugador);
                if (pos >= 0) {
                    fseek(archi, pos, SEEK_SET);
                    fwrite(&jugador, sizeof(stJugador), 1, archi);
                }
            }
        }
        fclose(archi);
    }
}

/**Hecha por Luciana_guarda jugador en archivo**/

int guardaJugadorArchivo(stJugador jugador) {
    FILE *archi = fopen(AR_JUGADORES, "ab");
    int resultado = 0; // 0 = error, 1 = éxito

    if (archi) {
        if (fwrite(&jugador, sizeof(stJugador), 1, archi) == 1) {
            resultado = 1;
        }
        fclose(archi);
    }

    return resultado;
}
