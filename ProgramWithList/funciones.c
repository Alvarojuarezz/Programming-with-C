#include "definiciones.h"
#include "funciones.h"
#include "listas.h"


struct equipo *insertar_equipo(struct equipo *equipos)
{

    equipos = (struct equipo*)malloc(sizeof(struct equipo));

    char *buffer;
    int longitud;
    buffer = (char*)malloc(sizeof(char)*255);

    fflush(stdin);
    printf("Introduzca el identificador del equipo:");gets(buffer);
    longitud = strlen(buffer);
    equipos->ident = (char*)malloc(sizeof(char)*(longitud+1));
    strcpy(equipos->ident,buffer);

    fflush(stdin);
    printf("Introduzca el nombre del equipo:");gets(buffer);
    longitud = strlen(buffer);
    equipos->nombre = (char*)malloc(sizeof(char)*(longitud+1));
    strcpy(equipos->nombre,buffer);

    fflush(stdin);
    printf("Introduzca el n%cmero de corredores: ",163);gets(buffer);
    equipos->num_corredores = atoi(buffer);

    // Solicitar nombres de ciclistas
    for (int i = 0; i < equipos->num_corredores; i++) {
        printf("Introduce el nombre del ciclista %d: ", i + 1);
        gets(buffer);
        longitud = strlen(buffer);
        equipos->ciclistas = (char *)malloc(sizeof(char) * (longitud + 1));
        strcpy(equipos->ciclistas , buffer);
    }

    fflush(stdin);
    printf("Introduzca el n%cmero de patrocinadores: ",163);gets(buffer);
    equipos->num_patroc = atoi(buffer);

    // Solicitar nombres de ciclistas
    for (int i = 0; i < equipos->num_patroc; i++) {
        printf("Introduce el nombre del patrocinador %d: ", i + 1);
        gets(buffer);
        longitud = strlen(buffer);
        equipos->patrocinadores = (char *)malloc(sizeof(char) * (longitud + 1));
        strcpy(equipos->patrocinadores , buffer);
    }


    free(buffer);
    return equipos;
};

struct pruebaCiclista *insertar_prueba(struct pruebaCiclista *pruebas)
{

    pruebas = (struct pruebaCiclista*)malloc(sizeof(struct pruebaCiclista));

    char *buffer;
    int longitud;
    buffer = (char*)malloc(sizeof(char)*255);

    fflush(stdin);
    printf("Introduzca la clave de la prueba ciclista: ");gets(buffer);
    longitud = strlen(buffer);
    pruebas->clave = (char*)malloc(sizeof(char)*(longitud+1));
    strcpy(pruebas->clave,buffer);

    fflush(stdin);
    printf("Introduzca el nombre de la prueba ciclista: ");gets(buffer);
    longitud = strlen(buffer);
    pruebas->nombre = (char*)malloc(sizeof(char)*(longitud+1));
    strcpy(pruebas->nombre,buffer);

    fflush(stdin);
    printf("Introduzca el a%co de celebraci%cn: ",164,162);gets(buffer);
    pruebas->ano_celebracion = atoi(buffer);


    fflush(stdin);
    printf("Introduzca el n%cmero de equipos: ",163);gets(buffer);
    pruebas->num_equipos = atoi(buffer);

    // Solicitar nombres de equipos
    for (int i = 0; i < pruebas->num_equipos; i++) {
        printf("Introduce el nombre del equipo %d: ", i + 1);
        gets(buffer);
        longitud = strlen(buffer);
        pruebas->equipos = (char *)malloc(sizeof(char) * (longitud + 1));
        strcpy(pruebas->equipos , buffer);
    }

    longitud = strlen(pruebas->clave) + snprintf(NULL, 0, "%d", pruebas->ano_celebracion) + 2; // 2 para "_"
    pruebas->ident = (char *)malloc(sizeof(char) * (longitud + 1));
    sprintf(pruebas->ident, "%s_%d", pruebas->clave, pruebas->ano_celebracion);

    printf("Identificador de la prueba: %s\n",pruebas->ident);
    fflush(stdin);

    free(buffer);
    return pruebas;
};
