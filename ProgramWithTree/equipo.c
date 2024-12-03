#include "arboles.h"
#include "equipo.h"

//FUNCIÓN DAR DE ALTA UN EQUIPO
struct equipo *insertar_equipo(struct equipo *equipos)
{
    equipos = (struct equipo*)malloc(sizeof(struct equipo));

    // Solicitar memoria para identificador y nombre
    char *buffer;
    int longitud;
    buffer = (char*)malloc(sizeof(char)*255);

    fflush(stdin);
    printf("Introduzca el identificador del equipo: ");
    gets(buffer);
    longitud = strlen(buffer);
    equipos->ident = (char*)malloc(sizeof(char)*(longitud+1));
    strcpy(equipos->ident,buffer);

    fflush(stdin);
    printf("Introduzca el nombre del equipo: ");
    gets(buffer);
    longitud = strlen(buffer);
    equipos->nombre = (char*)malloc(sizeof(char)*(longitud+1));
    strcpy(equipos->nombre,buffer);

    // Solicitar memoria para num_corredores y num_patroc
    equipos->num_corredores = (int*)malloc(sizeof(int));
    equipos->num_patroc = (int*)malloc(sizeof(int));

    // Solicitar número de corredores
    fflush(stdin);
    printf("Introduzca el n%cmero de corredores: ",163);
    gets(buffer);
    *(equipos->num_corredores) = atoi(buffer);

    // Solicitar memoria para ciclistas
    equipos->ciclistas = (char **)malloc(sizeof(char *) * (*(equipos->num_corredores)));
    // Solicitar nombres de ciclistas
    for (int i = 0; i < *(equipos->num_corredores); i++) {
        printf("Introduce el nombre del ciclista %d: ", i + 1);
        gets(buffer);
        longitud = strlen(buffer);
        equipos->ciclistas[i] = (char *)malloc(sizeof(char) * (longitud + 1));
        strcpy(equipos->ciclistas[i], buffer);
    }

    // Solicitar número de patrocinadores
    fflush(stdin);
    printf("Introduzca el n%cmero de patrocinadores: ",163);
    gets(buffer);
    *(equipos->num_patroc) = atoi(buffer);

    // Solicitar memoria para patrocinadores
    equipos->patrocinadores = (char **)malloc(sizeof(char *) * (*(equipos->num_patroc)));
    // Solicitar nombres de patrocinadores
    for (int i = 0; i < *(equipos->num_patroc); i++) {
        printf("Introduce el nombre del patrocinador %d: ", i + 1);
        gets(buffer);
        longitud = strlen(buffer);
        equipos->patrocinadores[i] = (char *)malloc(sizeof(char) * (longitud + 1));
        strcpy(equipos->patrocinadores[i], buffer);
    }

    free(buffer);
    return equipos;
}


// FUNCIÓN PARA MOSTRAR UN EQUIPO
void mostrar_equipo(P_NODO_ARBOL_EQUIPO ae)
{
    if (ae == NULL)
    {
        printf("No hay equipos dados de alta.\n");
    }
    else
    {
            printf("\nIdentificador del equipo: %s\n", ae->e->ident);
            printf("Nombre del equipo: %s\n", ae->e->nombre);
            printf("N%cmero de corredores: %d\n",163, *(ae->e->num_corredores));
            printf("Ciclistas:\n");
            for (int i = 0; i < *(ae->e->num_corredores); i++) {
                printf("- %s\n", ae->e->ciclistas[i]);
            }
            printf("N%cmero de patrocinadores: %d\n",163, *(ae->e->num_patroc));
            printf("Patrocinadores:\n");
            for (int i = 0; i < *(ae->e->num_patroc); i++) {
                printf("- %s\n", ae->e->patrocinadores[i]);
            }
    }
}
