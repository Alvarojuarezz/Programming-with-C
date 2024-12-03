#include <stdio.h>
#include <stdlib.h>

#include "arboles.h"
#include "prueba.h"
#include "equipo.h"

int menu2()
{
    int opc2 = 0;
    printf("\n***MENU LISTAR***\n");
    printf("1.Listar en PreOrder.\n");
    printf("2.Listar en inOrder.\n");
    printf("3.Listar en PostOrder.\n");
    printf("4.Ir para atr%cs.\n",160);
    printf("Opci%cn:",162);fflush(stdin);scanf("%d",&opc2);
    return opc2;
}

int menu()
{

    int opc = 0;
    int opc2 = 0;
    int cont_equipos = 0, cont_pruebas = 0;

    char *eqp_temp;
    P_NODO_ARBOL_EQUIPO ae = crearArbol_e();
    P_NODO_ARBOL_EQUIPO pe;

    char *prb_temp;
    P_NODO_ARBOL_PRUEBA apc = crearArbol_pc();
    P_NODO_ARBOL_PRUEBA ppc;

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

        switch (opc)
        {

            //ALTA CICLISTA
            case 1:
                    eqp_temp = insertar_equipo(eqp_temp);
                    ae = insertar_e(ae,eqp_temp);
                    cont_equipos++;
                    printf("\n****Equipo insertado con %cxito****\n",130);
                    break;

            //BAJA EQUIPO
            case 2:
                    printf("Introduzca el identificador del equipo que desea eliminar: ");
                    scanf("%s", buffer);

                    // Buscar el equipo en el árbol
                    P_NODO_ARBOL_EQUIPO equipo_encontrado = encontrar_e(ae, buffer);

                    if (equipo_encontrado != NULL) {
                        // Eliminar el equipo encontrado
                        ae = eliminar_e(ae, equipo_encontrado->e);
                        cont_equipos--;
                        printf("\nEquipo eliminado con %cxito.\n",130);
                    } else {
                        printf("\nEl equipo con identificador %s no existe.\n", buffer);
                    }
                    break;

            //ALTA PRUEBA
            case 3:
                    prb_temp = insertar_prueba(prb_temp);
                    apc = insertar_pc(apc , prb_temp);
                    cont_pruebas++;
                    printf("\n****Prueba insertada con %cxito****\n",130);
                    break;

            //BAJA PRUEBA MEDIANTE IDENTIFICADOR
            case 4:
                    printf("Introduzca el identificador de la prueba que desea eliminar: ");
                    scanf("%s", buffer);

                    // Buscar el equipo en el árbol
                    P_NODO_ARBOL_PRUEBA prueba_encontrada = encontrar_pc_ident(apc, buffer);

                    if (prueba_encontrada != NULL) {
                        // Eliminar el equipo encontrado
                        apc = eliminar_pc_ident(apc, prueba_encontrada->e);
                        cont_pruebas--;
                        printf("\nPrueba eliminada con %cxito.\n",130);
                    } else {
                        printf("\nLa prueba con identificador %s no existe.\n", buffer);
                    }
                    break;

            //BAJA PRUEBA MEDIANTE CLAVE
            case 5:
                    printf("Introduzca la clave de la prueba que desea eliminar: ");
                    scanf("%s", buffer);

                    // Buscar el equipo en el árbol
                    P_NODO_ARBOL_PRUEBA prueba_encontrada1 = encontrar_pc_clave(apc, buffer);

                    if (prueba_encontrada1 != NULL) {
                        // Eliminar el equipo encontrado
                        apc = eliminar_pc_clave(apc, prueba_encontrada1->e);
                        cont_pruebas--;
                        printf("\nPrueba eliminada con %cxito.\n",130);
                    } else {
                        printf("\nLa prueba con clave %s no existe.\n", buffer);
                    }
                    break;

            //LISTAR DATOS
            case 6:
                opc2 = menu2();
                switch(opc2)
                {
                case 1:
                    preOrder_e(ae);
                    preOrder_pc(apc);
                    break;
                case 2:
                    inOrder_e(ae);
                    inOrder_pc(apc);
                    break;
                case 3:
                    postOrder_e(ae);
                    postOrder_pc(apc);
                    break;
                case 4:
                    printf("\nSaliendo del men%c de listar...\n",163);
                    break;
                default:
                    printf("\nOpci%cn no v%clida. Int%cntelo de nuevo.\n",162,160,130);
                    break;
                }

                break;
            case 7:
                    printf("\nSaliendo del programa...\n");
                break;
            default:
                    printf("\nOpci%cn no v%clida. Int%cntelo de nuevo.\n",162,160,130);
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
