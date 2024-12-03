#include <stdio.h>
#include <stdlib.h>

#include "definiciones.h"
#include "listas.h"


int menu()
{
    int opc = 0;
    int opc2 = 0;
    int pcontador = 0;
    int econtador = 0;

    struct equipo *equipos = NULL;
    struct pruebaCiclista *pruebas = NULL;

    Listae ae = l_int_crear_e();
    Listapc apc = l_int_crear_pc();
    Posicione pe;
    Posicionpc ppc;

    char *buffer;
    buffer = (char*)malloc(sizeof(char)*255);



    while (opc != 7) {
        printf("\nMen%c:\n",163);
        printf("1. Alta equipo.\n");
        printf("2. Baja equipo.\n");
        printf("3. Alta prueba ciclista.\n");
        printf("4. Baja prueba ciclista dado su identificador.\n");
        printf("5. Baja prueba ciclista dada su clave.\n");
        printf("6. Listar datos.\n");
        printf("7. Salir.\n");
        printf("Seleccione una opci%cn:",162);
        scanf("%d", &opc);

        switch (opc) {
            //ALTA CICLISTA
            case 1:
                equipos = insertar_equipo(equipos);
                if(econtador == 0){
                    pe = l_int_primero_e(ae);
                    ae = l_int_insertar_e(ae, pe, equipos);
                    econtador++;
                }else{
                    pe = l_int_ultimo_e(ae);
                    ae=l_int_insertar_e(ae, pe, equipos);
                    econtador++;
                }
                break;
            //BAJA EQUIPO
            case 2:
                fflush(stdin);
                printf("Introduce el identificador del equipo a eliminar: ");
                fgets(buffer, 255, stdin); // Usar fgets para leer desde el teclado
                buffer[strcspn(buffer, "\n")] = '\0'; // Eliminar el car�cter de nueva l�nea
                //gets(buffer);
                pe=l_int_localizar_e(ae,buffer);
                if (pe != NULL) { // Verificar si se encontr� el elemento antes de borrar
                    ae = l_int_borrar_e(ae, pe);
                    printf("El equipo con identificador %s borrado con %cxito.\n",buffer,130);
                } else {
                    printf("El identificador no se encontr%c en la lista.\n",162);
                }
                break;
            //ALTA PRUEBA
            case 3:
                pruebas = insertar_prueba(pruebas);
                if(pcontador == 0){
                    ppc = l_int_primero_pc(apc);
                    apc = l_int_insertar_pc(apc, ppc, pruebas);
                    pcontador++;
                }else{
                    ppc = l_int_ultimo_pc(apc);
                    apc=l_int_insertar_pc(apc, ppc, pruebas);
                    pcontador++;
                }
                break;
            //BAJA PRUEBA MEDIANTE IDENTIFICADOR
            case 4:
                fflush(stdin);
                printf("Introduce el identificador de la prueba a eliminar: ");
                fgets(buffer, 255, stdin); // Usar fgets para leer desde el teclado
                buffer[strcspn(buffer, "\n")] = '\0'; // Eliminar el car�cter de nueva l�nea
                //gets(buffer);
                ppc=l_int_localizar_pc_ident(apc,buffer);
                if (ppc != NULL) { // Verificar si se encontr� el elemento antes de borrar
                    apc = l_int_borrar_pc(apc, ppc);
                    printf("El equipo con identificador %s borrado con %cxito.\n",buffer,130);
                } else {
                    printf("El identificador no se encontr%c en la lista.\n",162);
                }
                break;
            //BAJA PRUEBA MEDIANTE CLAVE
            case 5:
                fflush(stdin);
                printf("Introduce la clave de la prueba a eliminar: ");
                fgets(buffer, 255, stdin); // Usar fgets para leer desde el teclado
                buffer[strcspn(buffer, "\n")] = '\0'; // Eliminar el car�cter de nueva l�nea
                //gets(buffer);
                ppc=l_int_localizar_pc_clave(apc,buffer);
                if (ppc != NULL) { // Verificar si se encontr� el elemento antes de borrar
                    apc = l_int_borrar_pc(apc, ppc);
                    printf("El equipo con clave %s borrado con %cxito.\n",buffer,130);
                } else {
                    printf("El clave no se encontr%c en la lista.\n",162);
                }
                break;
            //LISTAR DATOS
            case 6:
                listar_equipos(ae);
                listar_pruebas(apc);
                break;
            case 7:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opci%cn no v%clida. Intentelo de nuevo.\n",162,160);
                break;

        }
    }
    return opc;
}

int main()
{
    int opc = menu();
    return 0;
}
