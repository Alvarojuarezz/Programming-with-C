#include "funciones.h"
#include "estructuras.h"


// Función para dar de alta ciclistas desde un fichero
struct ciclista *alta_ciclistas(const char *nombre_archivo, int *clcontador) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return NULL;
    }

    // Leer el número de ciclistas del archivo
    int num_ciclistas;
    fscanf(archivo, "%d", &num_ciclistas);

    // Reservar memoria para la estructura de ciclistas
    struct ciclista *ciclistas = (struct ciclista *)malloc(num_ciclistas * sizeof(struct ciclista));
    if (ciclistas == NULL) {
        printf("Error al asignar memoria.\n");
        fclose(archivo);
        return NULL;
    }


    // Leer cada ciclista del archivo
    for (int i = 0; i < num_ciclistas; i++) {
        char nombre[100];
        int ano_prof;
        // Leer el nombre y el año de profesionalización del ciclista desde el archivo
        fscanf(archivo, "%s %d", nombre, &ano_prof);

        // Asignar memoria y copiar el nombre del ciclista
        ciclistas[i].nombre = (char *)malloc((strlen(nombre) + 1) * sizeof(char));
        strcpy(ciclistas[i].nombre, nombre);

        // Asignar memoria y almacenar el año de profesionalización del ciclista
        ciclistas[i].ano_prof = (int *)malloc(sizeof(int));
        *(ciclistas[i].ano_prof) = ano_prof;
    }

    fclose(archivo);
    *clcontador = num_ciclistas;
    return ciclistas;
}

//Función para dar de alta un equipo
struct equipo *alta_equipo(struct equipo *e, int *econtador){

    char nombre_fichero[255];
    FILE *fequip;
    printf("Nombre del fichero para el equipo:(x.txt) ");
    scanf("%s", nombre_fichero);
    fequip = fopen(nombre_fichero, "w+");
    if (fequip == NULL) {
        printf("No se pudo abrir el fichero\n\n");
        return e;
    }

    char *buffer = (char *)malloc(sizeof(char)*255);
    int longitud;

    if(*econtador == 0)
        e = (struct equipo *)malloc(sizeof(struct equipo));
    else
        e = (struct equipo *)realloc(e,sizeof(struct equipo)*(*econtador + 1));

    fflush(stdin);
    printf("Introduce el identificador del equipo:");
    gets(buffer);
    longitud = strlen(buffer);
    e[*econtador].ident = (char *)malloc(sizeof(char)*(longitud+1));
    strcpy(e[*econtador].ident,buffer);

    fflush(stdin);
    printf("Introduce el nombre del equipo: ");
    gets(buffer);
    longitud = strlen(buffer);
    e[*econtador].nombre = (char *)malloc(sizeof(char)*(longitud+1));
    strcpy(e[*econtador].nombre,buffer);

    fflush(stdin);
    printf("Introduce el n%cmero de corredores: ",163);
    gets(buffer);
    longitud=strlen(buffer);
    e[*econtador].num_corredores = (int *)malloc(sizeof(int)*(longitud+1));
    *(e[*econtador].num_corredores) = atoi(buffer);

    fprintf(fequip,"%s\n",e[*econtador].ident);
    fprintf(fequip,"%s\n",e[*econtador].nombre);
    fprintf(fequip,"%d\n",*(e[*econtador].num_corredores));
    fflush(stdin);

    e[*econtador].ciclistas = (char **)malloc(sizeof(char *) * (*(e[*econtador].num_corredores)));

    // Solicitar nombres de ciclistas
    for (int i = 0; i < *(e[*econtador].num_corredores); i++) {
        printf("Introduce el nombre del ciclista %d: ", i + 1);
        gets(buffer);
        longitud = strlen(buffer);
        e[*econtador].ciclistas[i] = (char *)malloc(sizeof(char) * (longitud + 1));
        strcpy(e[*econtador].ciclistas[i], buffer);

        // Escribir el nombre del ciclista en el fichero
        fprintf(fequip, "%s\n", e[*econtador].ciclistas[i]);
    }

    // Solicitar el numero de patrocinadores
    printf("Introduce el n%cmero de patrocinadores: ",163);
    gets(buffer);
    e[*econtador].num_patroc = atoi(buffer);

    longitud = strlen(buffer);
    e[*econtador].num_patroc = (int *)malloc(sizeof(int) * (longitud + 1));
    *e[*econtador].num_patroc = atoi(buffer);
    fprintf(fequip, "%d\n", *e[*econtador].num_patroc);

    e[*econtador].patrocinadores = (char **)malloc(sizeof(char *) * (*(e[*econtador].num_patroc)));

    // Solicitar nombres de patrocinadores
    for (int i = 0; i < *e[*econtador].num_patroc; i++) {
        printf("Introduce el nombre del patrocinador %d: ", i + 1);
        gets(buffer);
        longitud = strlen(buffer);
        e[*econtador].patrocinadores[i] = (char *)malloc(sizeof(char) * (longitud + 1));
        strcpy(e[*econtador].patrocinadores[i], buffer);

        // Escribir el nombre del patrocinador en el fichero
        fprintf(fequip, "%s\n", e[*econtador].patrocinadores[i]);
    }

    (*econtador)++;
    free(buffer);
    fclose(fequip);
    return e;
};

//Función para dar de baja un equipo
struct equipo *baja_equipo(struct equipo *e, int *econtador) {
    FILE *archivo_ident = fopen("identequip.txt", "r");
    if (archivo_ident == NULL) {
        printf("No se pudo abrir el archivo de identificadores.\n");
        return e;
    }

    char buffer[255];
    printf("Introduce el identificador del equipo que desea eliminar: ");
    fgets(buffer, sizeof(buffer), archivo_ident);
    // Eliminar el carácter de nueva línea al final de la cadena
    buffer[strcspn(buffer, "\n")] = '\0';

    // Buscar el equipo con el identificador proporcionado en todos los registros
    for (int i = 0; i < *econtador; i++) {
        if (strcmp(e[i].ident, buffer) == 0) {
            // Liberar memoria asignada para el identificador, nombre y número de corredores
            free(e[i].ident);
            free(e[i].nombre);
            free(e[i].num_corredores);

            // Liberar memoria de los ciclistas
            for (int j = 0; j < *(e[i].num_corredores); j++) {
                free(e[i].ciclistas[j]);
            }
            free(e[i].ciclistas);

            // Liberar memoria de los patrocinadores
            for (int k = 0; k < *(e[i].num_patroc); k++) {
                free(e[i].patrocinadores[k]);
            }
            free(e[i].patrocinadores);

            // Desplazar los equipos restantes si hay más después de este
            for (int j = i; j < *econtador - 1; j++) {
                e[j] = e[j + 1];
            }

            // Decrementar el contador de equipos
            (*econtador)--;

            printf("\nEl equipo ciclista con identificador %s ha sido dado de baja.\n", buffer);
            fclose(archivo_ident);
            return e;
        }
    }

    printf("\nNo se encontr%c ning%cn equipo ciclista con identificador %s.\n",162,163, buffer);
    fclose(archivo_ident);
    return e;
};

// Función para dar de alta una prueba ciclista

struct pruebaCiclista *alta_prueba_ciclista(struct pruebaCiclista *p, int *contador)
{
    char nombre_fichero[255];FILE * fprueb;
    printf("Nombre del fichero para las pruebas:(x.txt) ");scanf("%s", nombre_fichero);
    fprueb = fopen(nombre_fichero, "w+");
    if (fprueb == NULL) {
        printf("No se pudo abrir el fichero\n\n");
        return;
    }

    char *buffer = (char *)malloc(sizeof(char)*255);
    int longitud;

    if(*contador == 0)
        p = (struct pruebaCiclista *)malloc(sizeof(struct pruebaCiclista));
    else
        p = (struct pruebaCiclista *)realloc(p,sizeof(struct pruebaCiclista)*(*contador + 1));


    fflush(stdin);
    printf("Introduce la nueva clave:");gets(buffer);
    longitud = strlen(buffer);
    p[*contador].clave = (char *)malloc(sizeof(char)*(longitud+1));
    strcpy(p[*contador].clave,buffer);

    fflush(stdin);
    printf("Introduce el nuevo nombre:");gets(buffer);
    longitud = strlen(buffer);
    p[*contador].nombre = (char *)malloc(sizeof(char)*(longitud+1));
    strcpy(p[*contador].nombre,buffer);

    fflush(stdin);
    printf("Introduce el a%co de celebracion:",164);gets(buffer);
    longitud = strlen(buffer);
    p[*contador].ano_celebracion = (int *)malloc(sizeof(int)*(longitud+1));
    *(p[*contador].ano_celebracion) = atoi(buffer);

    fflush(stdin);
    printf("Introduce el n%cmero de equipos:",163);gets(buffer);
    longitud = strlen(buffer);
    p[*contador].num_equipos = (int *)malloc(sizeof(int)*(longitud+1));
    *(p[*contador].num_equipos) = atoi(buffer);

    p[*contador].equipos = (struct equipo *)malloc(sizeof(struct equipo) * (*(p[*contador].num_equipos)));

    fprintf(fprueb,"%s\n",p[*contador].clave);
    fprintf(fprueb,"%s\n",p[*contador].nombre);
    fprintf(fprueb,"%d\n",*(p[*contador].ano_celebracion));
    fprintf(fprueb,"%d\n",*(p[*contador].num_equipos));

    fflush(stdin);

    longitud = strlen(p[*contador].clave) + snprintf(NULL, 0, "%d", *(p[*contador].ano_celebracion)) + 2; // 2 para "_"
    p[*contador].ident = (char *)malloc(sizeof(char) * (longitud + 1));
    sprintf(p[*contador].ident, "%s_%d", p[*contador].clave, *(p[*contador].ano_celebracion));

    fflush(stdin);


    for (int i = 0; i < *(p[*contador].num_equipos); i++) {
        printf("Introduce el nombre del equipo %d: ", i + 1);
        gets(buffer);
        longitud = strlen(buffer);
        p[*contador].equipos[i]= (char *)malloc(sizeof(char) * (longitud + 1));
        strcpy(p[*contador].equipos[i], buffer);

        // Escribir el nombre del equipo en el fichero
        fprintf(fprueb, "%s\n", p[*contador].equipos[i]);
    }
    fprintf(fprueb,"%s\n",p[*contador].ident);
    printf("Identificador de la prueba: %s\n",p[*contador].ident);
    fflush(stdin);


    (*contador)++;
    fclose(fprueb);
    free(buffer);
    return p;
};


// Función para dar de baja una prueba ciclista mediante el identificador
struct pruebaCiclista *baja_prueba_ident(struct pruebaCiclista *p, int *contador) {
    int i, j;
    FILE *archivo_ident = fopen("identprb.txt", "r"); // Nombre del archivo de identificadores
    char buffer[255];
    if (archivo_ident == NULL) {
        printf("No se pudo abrir el archivo de identificadores.\n");
        return p;
    }
    printf("Introduce el identificador de la prueba que desea eliminar: ");
    fflush(stdin);
    fgets(buffer, sizeof(buffer), archivo_ident);
    // Eliminar el carácter de nueva línea del buffer
    buffer[strcspn(buffer, "\n")] = '\0';

    for (i = 0; i < *contador; i++) {
        if (strcmp(p[i].ident, buffer) == 0) { // Encontramos la prueba a dar de baja
            // Liberar memoria de los campos de la prueba ciclista
            free(p[i].clave);
            free(p[i].nombre);
            free(p[i].ano_celebracion);
            free(p[i].num_equipos);
            free(p[i].ident);

            // Liberar memoria de los nombres de los equipos
            for (j = 0; j < *(p[i].num_equipos); j++) {
                free(p[i].equipos[j]);
            }

            // Liberar memoria del arreglo de equipos
            free(p[i].equipos);
            // Desplazar los elementos restantes si hay más después de este
            for (j = i; j < *contador - 1; j++) {
                p[j] = p[j + 1];
            }

            // Redimensionar el arreglo de pruebas
            p = (struct pruebaCiclista *)realloc(p, sizeof(struct pruebaCiclista) * (*contador - 1));
            (*contador)--;
            printf("\nLa prueba ciclista con identificador %s ha sido dada de baja.\n", buffer);
            fclose(archivo_ident);
            return p;
        }
    }
    printf("\nNo se encontr%c ninguna prueba ciclista con identificador %s.\n",162, buffer);
    fclose(archivo_ident);
    return p;
};

// Función para dar de baja una prueba ciclista mediante la clave
struct pruebaCiclista *baja_prueba_clave(struct pruebaCiclista *p, int *contador) {
    int i, j;
    FILE *archivo_ident = fopen("claveprb.txt", "r"); // Nombre del archivo de identificadores
    char buffer[255];
    if (archivo_ident == NULL) {
        printf("No se pudo abrir el archivo de identificadores.\n");
        return p;
    }
    printf("Introduce la clave de la prueba que desea eliminar: ");
    fflush(stdin);
    fgets(buffer, sizeof(buffer), archivo_ident);
    // Eliminar el carácter de nueva línea del buffer
    buffer[strcspn(buffer, "\n")] = '\0';

    for (i = 0; i < *contador; i++) {
        if (strcmp(p[i].clave, buffer) == 0) { // Encontramos la prueba a dar de baja
            // Liberar memoria de los campos de la prueba ciclista
            free(p[i].clave);
            free(p[i].nombre);
            free(p[i].ano_celebracion);
            free(p[i].num_equipos);
            free(p[i].ident);

            // Liberar memoria de los nombres de los equipos
            for (j = 0; j < *(p[i].num_equipos); j++) {
                free(p[i].equipos[j]);
            }

            // Liberar memoria del arreglo de equipos
            free(p[i].equipos);
            // Desplazar los elementos restantes si hay más después de este
            for (j = i; j < *contador - 1; j++) {
                p[j] = p[j + 1];
            }

            // Redimensionar el arreglo de pruebas
            p = (struct pruebaCiclista *)realloc(p, sizeof(struct pruebaCiclista) * (*contador - 1));
            (*contador)--;
            printf("\nLa prueba ciclista con identificador %s ha sido dada de baja.\n", buffer);
            fclose(archivo_ident);
            return p;
        }
    }
    printf("\nNo se encontr%c ninguna prueba ciclista con identificador %s.\n",162, buffer);
    fclose(archivo_ident);
    return p;
};

// Función para mostrar
void listar_datos(struct ciclista *ciclistas, int num_ciclistas) {
    printf("Ciclistas:\n");
    for (int i = 0; i < num_ciclistas; i++) {
        printf("Nombre: %s, A%co de profesional: %d\n",ciclistas[i].nombre,164,*(ciclistas[i].ano_prof));
    }

}

