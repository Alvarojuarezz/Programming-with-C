#include "estructuras.h"
#include "funciones.h"


int menu()
{
    int contador = 0,opcion = 0, econtador = 0,clcontador , num_ciclistas = 0, num_patrocinadores= 0, num_pruebas = 0;
    struct pruebaCiclista *pruebas; // Declarar las variables globales
    struct equipo *equipos;
    struct ciclista *ciclistas;
    char nombre_fichero[255];

    int opc;
    ciclistas = alta_ciclistas("ciclistas.txt", &clcontador);
    if (ciclistas != NULL) {
        printf("Ciclistas dados de alta desde el archivo.\n");
        num_ciclistas = clcontador;
    }
    while (opc != 7) {
        printf("\nMenu:\n");
        printf("1. Dar de alta equipos ciclistas\n");
        printf("2. Dar de baja equipos ciclistas\n");
        printf("3. Dar de alta pruebas ciclistas\n");
        printf("4. Dar de baja pruebas por identificador\n");
        printf("5. Dar de baja pruebas por clave\n");
        printf("6. Listar datos\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion:");
        scanf("%d", &opc);

        switch (opc) {
            case 1:
                equipos = alta_equipo(equipos, &econtador);
                break;
           case 2:
                equipos = baja_equipo(equipos, &econtador);
                break;
            case 3:
                //pruebas = alta_prueba_ciclista(nombre_fichero, &contador);
                pruebas = alta_prueba_ciclista( pruebas ,&contador);
                break;
            case 4:
                pruebas = baja_prueba_ident( pruebas ,&contador);
                break;
            case 5:
                pruebas = baja_prueba_clave( pruebas ,&contador);
                break;
            case 6:
                    if (contador >0 ) {
                        printf("\nPruebas Ciclistas:\n");
                        for (int i = 0; i < contador; i++) {
                            printf("\nClave: %s", pruebas[i].clave);
                            printf("\nNombre: %s", pruebas[i].nombre);
                            printf("\nA%co de celebraci%cn: %d",164 ,162,*(pruebas[i].ano_celebracion));
                            printf("\nN%cmero de equipos: %d",163, *(pruebas[i].num_equipos));
                            printf("\nEquipos:\n");
                            for (int j = 0; j < *(pruebas[i].num_equipos); j++) {
                                printf("- %s \n", pruebas[i].equipos[j]);
                            }
                            printf("\nIdentificador: %s\n", pruebas[i].ident);
                        }
                    }
                    else
                    {
                        printf("No hay pruebas ciclistas dadas de alta.\n");
                    }

                break;
            case 7:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intentelo de nuevo.\n");

        }
    }
    return opc;
}

int main()
{

    int opcion = menu();
    return 0;
}
