#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
// Las constantes se definen para agilizar la programación
#define MAX_PRUEBAS 10
#define MAX_EQUIPOS 10
#define MAX_CORREDORES 10
#define MAX_PATROCINADORES 5
#define A 50
#define B 30
#define C 20
#define D 100

int i;
char nombfichprb[MAX_PRUEBAS], resp[3];
int create=0, clcreate = 0 ,tcreate = 0;
char nombre_fichero[D];
char ident_prb[B], ident_equipo[B];
char clave[MAX_PRUEBAS],nombre[MAX_PRUEBAS] , nombre_patroc[MAX_PATROCINADORES];
int num_equipos,ano_celebracion,ident,num_patroc,num_corredores,ano_prof;
FILE *fprueb , *fequip;
bool status;

typedef struct {
    char ident[C];
    char nombre[A];
    int ano_prof;
} ciclista;

typedef struct {
    char ident[C];
    char nombre[A];
    int num_corredores;
    char patrocinadores[MAX_PATROCINADORES][A];
    int num_patroc;
} equipo;

typedef struct {
    char clave[C];
    int ano_celebracion;
    char nombre[A];
    int num_equipos;
    char ident[B];
} pruebaCiclista;

pruebaCiclista pruebas[MAX_PRUEBAS];
equipo equipos[MAX_EQUIPOS];
ciclista ciclistas[MAX_CORREDORES];

int num_pruebas = 0;
int num_corredores = 0;
int num_equipos = 0;


struct pruebaCiclista *alta_prueba_ciclista(struct pruebaCiclista *pruebas, int *contador) {
    char nombre_fichero[255];
    FILE *fprueb;

    printf("Nombre del fichero para las pruebas (x.txt): ");
    scanf("%s", nombre_fichero);
    fprueb = fopen(nombre_fichero, "r");
    if (fprueb == NULL) {
        printf("No se pudo abrir el fichero\n\n");
        return pruebas;
    }

    // Reasigna la memoria para el array de pruebas
    if (*contador == 0)
        pruebas = (struct pruebaCiclista *)malloc(sizeof(struct pruebaCiclista));
    else
        pruebas = (struct pruebaCiclista *)realloc(pruebas, sizeof(struct pruebaCiclista) * (*contador + 1));


    // Puntero auxiliar para leer desde el archivo
    char buffer[255];
    int longitud;

    // Lee la clave
    fgets(buffer, 255, fprueb);
    longitud = strlen(buffer);
    pruebas[*contador].clave = (char *)malloc(sizeof(char)*(longitud+1));
    strcpy(pruebas[*contador].clave,buffer);

    // Lee el nombre
    fgets(buffer, 255, fprueb);
    longitud = strlen(buffer);
    pruebas[*contador].nombre = (char *)malloc(sizeof(char)*(longitud+1));
    strcpy(pruebas[*contador].nombre,buffer);

    // Lee el año de celebración
    fgets(buffer, 255, fprueb);
    pruebas[*contador].ano_celebracion = (int *)malloc(sizeof(int));
    *(pruebas[*contador].ano_celebracion) = atoi(buffer);

    // Lee el número de equipos
    fgets(buffer, 255, fprueb);
    pruebas[*contador].num_equipos = (int *)malloc(sizeof(int));
    *(pruebas[*contador].num_equipos) = atoi(buffer);

    // Genera el identificador
    longitud = strlen(pruebas[*contador].clave) + snprintf(NULL, 0, "%d", *(pruebas[*contador].ano_celebracion)) + 1; // +1 para el guión bajo
    pruebas[*contador].ident = (char *)malloc(sizeof(char) * (longitud + 1));
    sprintf(pruebas[*contador].ident, "%s_%d", pruebas[*contador].clave, *(pruebas[*contador].ano_celebracion));

    // Lee los nombres de los equipos
    pruebas[*contador].equipos = (char **)malloc(sizeof(char *) * (*(pruebas[*contador].num_equipos)));
    for (int i = 0; i < *(pruebas[*contador].num_equipos); i++) {
        fgets(buffer, 255, fprueb);
        longitud = strlen(buffer);
        pruebas[*contador].equipos[i] = (char *)malloc(sizeof(char)*(longitud+1));
        strcpy(pruebas[*contador].equipos[i],buffer);
    }

    // Imprime el identificador de la prueba
    printf("Identificador de la prueba: %s", pruebas[*contador].ident);


    printf("\nPrueba dada de alta con exito.\n");
    // Incrementa el contador
    (*contador)++;
    // Cierra el archivo
    fclose(fprueb);
    return pruebas;
};

void baja_prueba_clave() { //Función para de baja una prueba mediante la clave

    FILE *archivo_claves = fopen("clavesprb.txt", "r"); // Nombre del archivo de claves
    if (archivo_claves == NULL) {
        printf("No se pudo abrir el archivo de claves.\n");
        return;
    }

    printf("Clave de la prueba a eliminar: ");
    fflush(stdin);
    fscanf(archivo_claves, "%s", clave);

    bool encontrada = false;
    int pruebas_encontradas = 0;
    for (int i = 0; i < num_pruebas; i++) {
        if (strcmp(pruebas[i].clave, clave) == 0) {
            encontrada = true;
            pruebas_encontradas++;
        }
    }

    if (encontrada == true) {
        printf("\nSe encontraron %d pruebas asociadas a la clave %s.\n", pruebas_encontradas, clave);
        printf("Desea continuar con la eliminacion de la/las pruebas/s?(si/no): ");
        fflush(stdin);
        fscanf(stdin, "%s", resp);

        if (strcmp(resp, "si") == 0 || strcmp(resp, "Si") == 0) {
            for (int i = 0; i < num_pruebas; i++) {
                if (strcmp(pruebas[i].clave, clave) == 0) {
                    // Eliminar la prueba
                    strcpy(pruebas[i].clave, "");
                    strcpy(pruebas[i].ident,"");
                    pruebas[i].ano_celebracion=0;
                    pruebas[i].num_equipos=0;
                    strcpy(pruebas[i].nombre,"");
                    num_pruebas--;
                    printf("La prueba con clave %s fue eliminada exitosamente.\n", clave);
                }
            }
        } else {
            printf("La eliminacion de pruebas fue cancelada por el usuario.\n");
        }
    } else {
        printf("\nNo se encontro ninguna prueba asociada a la clave proporcionada.\n");
    }

    fclose(archivo_claves);
}

void baja_prueba_ident() { //funcion para dar de baja una prueba mediante el identificador

    FILE *archivo_ident = fopen("identprb.txt", "r"); // Nombre del archivo de identificadores
    if (archivo_ident == NULL) {
        printf("No se pudo abrir el archivo de identificadores.\n");
        return;
    }

    char ident[30]; // Ajusta el tamaño según la longitud máxima esperada del identificador
    printf("Identificador de la prueba a eliminar (clave_ano): ");
    fflush(stdin);
    fscanf(archivo_ident, "%s", ident_prb);

    bool encontrada = false;
    int pruebas_encontradas = 0;
    for (int i = 0; i < num_pruebas; i++) {
        if (strcmp(pruebas[i].ident, ident_prb) == 0) {
            encontrada = true;
            pruebas_encontradas++;
        }
    }

    if (encontrada == true) {
            for (int i = 0; i < pruebas_encontradas; i++) {
                if (strcmp(pruebas[i].ident, ident_prb) == 0) {
                // Eliminar la prueba
                strcpy(pruebas[i].clave, "");
                strcpy(pruebas[i].ident,"");
                pruebas[i].ano_celebracion=0;
                pruebas[i].num_equipos=0;
                strcpy(pruebas[i].nombre,"");
                // Eliminar los equipos dentro de la prueba
                for (int j = 0; j < pruebas[i].num_equipos; j++) {
                    strcpy(pruebas[i].equipos[j].nombre, "");
                    pruebas[i].equipos[j].num_corredores = 0;
                    // Eliminar los corredores dentro del equipo
                    for (int k = 0; k < MAX_CORREDORES; k++) {
                        strcpy(pruebas[i].equipos[j].ciclistas[k].nombre, "");
                        pruebas[i].equipos[j].ciclistas[k].ano_prof = 0;
                    }
                }
                num_pruebas--;
                printf("La prueba con identificador %s fue eliminada exitosamente.\n", ident_prb);
            }
            }
    } else {
        printf("\nNo se encontro ninguna prueba asociada al identificador proporcionado.\n");
    }

    fclose(archivo_ident);
}

void alta_equipos() { // Funcion para dar de alta un equipo

    printf("Nombre del fichero para el equipo:(x.txt) ");
    scanf("%s", nombre_fichero);
    fequip = fopen(nombre_fichero, "w+");
    if (fequip == NULL) {
        printf("No se pudo abrir el fichero\n\n");
        return;
    }

    printf("\nNuevo identificador: ");
    fflush(stdin);
    scanf("%s", clave);
    printf("Nuevo nombre: ");
    fflush(stdin);
    gets(nombre);
    printf("Numero de corredores: ");
    fflush(stdin);
    scanf("%d", &num_corredores);



    strcpy(pruebas[create].equipos[tcreate].ident, clave);
    strcpy(pruebas[create].equipos[tcreate].nombre, nombre);
    pruebas[create].equipos[tcreate].num_corredores = num_corredores;

    fprintf(fequip, "%s\n",pruebas[create].equipos[tcreate].ident);
    fprintf(fequip, "%s\n", pruebas[create].equipos[tcreate].nombre);
    fprintf(fequip, "%d\n", pruebas[create].equipos[tcreate].num_corredores);

    for (int i = 0; i < num_corredores; i++) {
        char nombre_corredor[A];
        printf("Nombre del corredor %d: ", i + 1);
        fflush(stdin);
        scanf("%s", nombre_corredor);
        strcpy(pruebas[create].equipos[tcreate].ciclistas[i].nombre,nombre_corredor);
        fprintf(fequip, "%s\n",pruebas[create].equipos[tcreate].ciclistas[i].nombre);
    }

    printf("Numero de patrocinadores:");
    fflush(stdin);
    scanf("%d",&num_patroc);
    pruebas[create].equipos[tcreate].num_patroc = num_patroc;
    fprintf(fequip,"%d\n",pruebas[create].equipos[tcreate].num_patroc);

    for(i = 0; i < num_patroc ; i++){
        printf("Nombre del patrocinador %d: ", i + 1);
        fflush(stdin);
        scanf("%s",nombre_patroc);
        strcpy(pruebas[create].equipos[tcreate].patrocinadores,nombre_patroc);
        fprintf(fequip, "%s\n",pruebas[create].equipos[tcreate].patrocinadores);
    }
    for (int i = 0; i < num_patroc; i++) {
        printf("Nombre del patrocinador %d: ", i + 1);
        fgets(nombre_patroc, sizeof(nombre_patroc), stdin);
        nombre_patroc[strcspn(nombre_patroc, "\n")] = '\0'; // Eliminar el salto de línea del final del nombre
        strcpy(pruebas[create].equipos[tcreate].patrocinadores[i], nombre_patroc); // Copiar el nombre del patrocinador al array del equipo
    }


    num_equipos++;
    tcreate++;
    fclose(fequip); // Cerramos el fichero
}

void baja_equipos() { //Función para eliminar equipos del sistema

    FILE *archivo_ident = fopen("identequipo.txt", "r"); // Nombre del archivo de identificadores
    if (archivo_ident == NULL) {
        printf("No se pudo abrir el archivo de identificadores.\n");
        return;
    }

    printf("Identificador del equipo a eliminar: ");
    fflush(stdin);
    fscanf(archivo_ident, "%s", ident_equipo);

    bool encontrada = false;
    int equipos_encontrados = 0;
    for (int i = 0; i < MAX_PRUEBAS; i++) {
        if (strcmp(pruebas[i].ident, ident_equipo) == 0) {
            encontrada = true;
            equipos_encontrados++;
        }
    }

    if (encontrada == true) {

            for (int i = 0; i < MAX_PRUEBAS; i++) {
                if (strcmp(equipos[i].ident, ident_equipo) == 0) {
                    // Eliminar la prueba
                    for (int i = 0; i < MAX_EQUIPOS; i++){
                        strcpy(pruebas[create].equipos[tcreate].ident, "");
                        strcpy(pruebas[create].equipos[tcreate].nombre, "");
                        pruebas[create].equipos[tcreate].num_corredores = 0;
                        pruebas[create].equipos[tcreate].num_patroc = 0;
                    }
                    for (int i = 0; i < MAX_CORREDORES; i++) {
                        strcpy(pruebas[create].equipos[tcreate].ciclistas[i].ident, "");
                        strcpy(pruebas[create].equipos[tcreate].ciclistas[i].nombre, "");
                        pruebas[create].equipos[tcreate].ciclistas[i].ano_prof = 0;
                    }
                    for (int i = 0; i < MAX_PATROCINADORES; i++) {
                        strcpy(pruebas[create].equipos[tcreate].patrocinadores[i], "");
                    }

                    num_equipos--;
                    printf("La prueba con identificador %s fue eliminada exitosamente.\n", ident_equipo);
                }
            }

    } else {
        printf("\nNo se encontro ninguna prueba asociada al identificador proporcionado.\n");
    }

    fclose(archivo_ident);
}

/*
void guardar_estado() { //funcion para guardar el estado del programa en un fichero
    printf("Introduce el nombre del fichero para guardar el estado del programa: ");
    scanf("%s", nombre_fichero);

    FILE *archivo_estado = fopen(nombre_fichero, "w+");
    if (archivo_estado == NULL) {
        printf("No se pudo abrir el archivo para guardar el estado del programa.\n");
        return;
    }

    // Escribir el número de pruebas
    fprintf(archivo_estado, "%d\n", num_pruebas);

    // Escribir los datos de cada prueba
    for (int i = 0; i < num_pruebas; i++) {
        fprintf(archivo_estado, "%s\n", pruebas[i].clave);
        fprintf(archivo_estado, "%d\n", pruebas[i].ano_celebracion);
        fprintf(archivo_estado, "%s\n", pruebas[i].nombre);
        fprintf(archivo_estado, "%d\n", pruebas[i].num_equipos);

        // Escribir los datos de cada equipo en la prueba
        for (int j = 0; j < pruebas[i].num_equipos; j++) {
            fprintf(archivo_estado, "%s\n", pruebas[i].equipos[j].ident);
            fprintf(archivo_estado, "%s\n", pruebas[i].equipos[j].nombre);
            fprintf(archivo_estado, "%d\n", pruebas[i].equipos[j].num_corredores);

            // Escribir los datos de cada corredor en el equipo
            for (int k = 0; k < pruebas[i].equipos[j].num_corredores; k++) {
                fprintf(archivo_estado, "%s\n", pruebas[i].equipos[j].ciclistas[k].nombre);
            }

            // Escribir los nombres de los patrocinadores del equipo
            for (int k = 0; k < pruebas[i].equipos[j].num_patroc; k++) {
                fprintf(archivo_estado, "%s\n", pruebas[i].equipos[j].patrocinadores[k]);
            }
        }
    }

    fclose(archivo_estado);
    printf("Estado del programa guardado correctamente en el fichero %s\n", nombre_fichero);
}*/

void cargar_estado() {
    FILE *archivo_estado = fopen("estado.txt", "r");
    if (archivo_estado == NULL) {
        printf("No se pudo abrir el archivo para cargar el estado del programa.\n");
        return;
    }

    // Leer el número de pruebas
    fscanf(archivo_estado, "%d", &num_pruebas);

    // Leer los datos de cada prueba
    for (int i = 0; i < num_pruebas; i++) {
        fscanf(archivo_estado, "%s", pruebas[i].clave);
        fscanf(archivo_estado, "%d", &pruebas[i].ano_celebracion);
        fscanf(archivo_estado, "%s", pruebas[i].nombre);
        fscanf(archivo_estado, "%d", &pruebas[i].num_equipos);

        // Leer los datos de cada equipo en la prueba
        for (int j = 0; j < pruebas[i].num_equipos; j++) {
            fscanf(archivo_estado, "%s", pruebas[i].equipos[j].ident);
            fscanf(archivo_estado, "%s", pruebas[i].equipos[j].nombre);
            fscanf(archivo_estado, "%d", &pruebas[i].equipos[j].num_corredores);

            // Leer los datos de cada corredor en el equipo
            for (int k = 0; k < pruebas[i].equipos[j].num_corredores; k++) {
                fscanf(archivo_estado, "%s", pruebas[i].equipos[j].ciclistas[k].nombre);
            }

            // Leer los nombres de los patrocinadores del equipo
            for (int k = 0; k < pruebas[i].equipos[j].num_patroc; k++) {
                fscanf(archivo_estado, "%s", nombre_patroc[k]);
                pruebas[i].equipos[j].patrocinadores[j][k] = strdup(nombre_patroc[k]);
            }
        }
    }
    printf("Lectura de fichero correctamente.\n");
    fclose(archivo_estado);
}


void listar_datos() { // función para listar los datos del sistema

        printf("Listando datos del programa:\n");
        for (int i = 0; i < num_pruebas; i++) {
            printf("Prueba Ciclista: %s\n", pruebas[i].nombre);
            printf("Clave: %s\n", pruebas[i].clave);
            printf("Ano de celebracion: %d\n", pruebas[i].ano_celebracion);
            printf("Equipos participantes:\n");
            for (int j = 0; j < pruebas[i].num_equipos; j++) {
                printf("  Equipo: %s\n", pruebas[i].equipos[j].nombre);
                printf("  Corredores:\n");
                for (int k = 0; k < pruebas[i].equipos[j].num_corredores; k++) {
                    printf("    %s\n", pruebas[i].equipos[j].ciclistas[k].nombre);
                }
                printf("  Patrocinadores:\n");
                for (int k = 0; k < pruebas[i].equipos[j].num_patroc; k++) {
                    printf("    %s\n", pruebas[i].equipos[j].patrocinadores[k]);
                }
            }
        }
}

void alta_cl(){// función para dar de alta un ciclista

    printf("Identificador del nuevo corredor:");
    fflush(stdin);
    scanf("%s", clave);
    printf("Nuevo nombre: ");
    fflush(stdin);
    gets(nombre);
    printf("Ano de profesional: ");
    fflush(stdin);
    scanf("%d", &ano_prof);

    strcpy(pruebas[create].equipos[tcreate].ciclistas[clcreate].ident,clave);
    strcpy(pruebas[create].equipos[tcreate].ciclistas[clcreate].nombre,nombre);
    pruebas[create].equipos[tcreate].ciclistas[clcreate].ano_prof=ano_prof;

    num_corredores++;
    clcreate;
}


int main() {
    int opc;



    while (opc != 10) {
        printf("\nMenu:\n");
        printf("1. Dar de alta pruebas ciclistas\n");
        printf("2. Dar de baja pruebas por identificador\n");
        printf("3. Dar de baja pruebas por clave\n");
        printf("4. Dar de alta equipos ciclistas\n");
        printf("5. Dar de baja equipos ciclistas\n");
        printf("6. Dar de alta ciclista\n");
        printf("7. Guardar estado del programa\n");
        printf("8. Cargar estado del programa\n");
        printf("9. Listar datos\n");
        printf("10. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1:
                alta_pruebas();
                break;
            case 2:
                baja_prueba_ident();
                break;
            case 3:
                baja_prueba_clave();
                break;
            case 4:
                alta_equipos();
                break;
            case 5:
                baja_equipos();
                break;
            case 6:
                alta_cl();
                break;
            case 7:
                guardar_estado();
                break;
            case 8:
                cargar_estado();
                break;
            case 9:
                listar_datos();
                break;
            case 10:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intentelo de nuevo.\n");

        }
    }

    return 0;
}
