#include "arboles.h"
#include "prueba.h"


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

    // Solicitar memoria para ano_celebracion y num_equipos
    pruebas->ano_celebracion = (int*)malloc(sizeof(int));
    pruebas->num_equipos = (int*)malloc(sizeof(int));

    fflush(stdin);
    printf("Introduzca el a%co de celebraci%cn: ",164,162);gets(buffer);
    *(pruebas->ano_celebracion) = atoi(buffer);


    fflush(stdin);
    printf("Introduzca el n%cmero de equipos: ",163);gets(buffer);
    *(pruebas->num_equipos) = atoi(buffer);

    pruebas->equipos = (char **)malloc(sizeof(char *) * (*(pruebas->num_equipos)));
    // Solicitar nombres de equipos
    for (int i = 0; i < *(pruebas->num_equipos); i++) {
        printf("Introduce el nombre del equipo %d: ", i + 1);
        gets(buffer);
        longitud = strlen(buffer);
        pruebas->equipos[i] = (char *)malloc(sizeof(char) * (longitud + 1));
        strcpy(pruebas->equipos[i] , buffer);
    }

    longitud = strlen(pruebas->clave) + snprintf(NULL, 0, "%d", *(pruebas->ano_celebracion)) + 2; // 2 para "_"
    pruebas->ident = (char *)malloc(sizeof(char) * (longitud + 1));
    sprintf(pruebas->ident, "%s_%d", pruebas->clave, *(pruebas->ano_celebracion));

    printf("Identificador de la prueba: %s\n",pruebas->ident);
    fflush(stdin);

    free(buffer);
    return pruebas;
};

// FUNCIÓN PARA MOSTRAR UNA PRUEBA CICLISTA
void mostrar_prueba(P_NODO_ARBOL_PRUEBA apc)
{
    if(apc == NULL)
    {
        printf("No hay pruebas dadas de alta.\n");
    }
    else
    {
            printf("\nIdentificador de la prueba: %s\n", apc->e->ident);
            printf("Clave de la prueba: %s\n", apc->e->clave);
            printf("Nombre de la prueba: %s\n", apc->e->nombre);
            printf("A%co de celebraci%cn: %d\n",164,162, *(apc->e->ano_celebracion));

            printf("N%cmero de equipos: %d\n",163, *(apc->e->num_equipos));
            printf("Equipos:\n");
            for (int i = 0; i < *(apc->e->num_equipos); i++) {
                printf("- %s\n", apc->e->equipos[i]);
            }
    }

}
