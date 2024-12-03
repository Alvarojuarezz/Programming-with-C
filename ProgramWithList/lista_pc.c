#include "listas.h"

struct nodo3* l_int_crear_pc(void)
{
   return (NULL);
}

struct nodo3* l_int_insertar_pc(struct nodo3 *l, struct nodo3 *pindice, struct pruebaCiclista *n)
{
    struct nodo3 *paux;
    paux = (struct nodo3 *) malloc(sizeof(struct nodo3));
    if (paux != NULL) {
        paux->n = n;
        if (l == NULL)
        {
            paux->psig = NULL;
            l = paux;
        }
        else
        {
            paux->psig = pindice->psig;
            pindice->psig = paux;
        }
    }
    return(l);
}

struct nodo3* l_int_inser_ppo_pc(struct nodo3 *l, struct pruebaCiclista *n)
{
    struct nodo3 *paux;

    paux = (struct nodo3 *) malloc(sizeof (struct nodo3));

    if (paux != NULL) {
       paux->n = n;

       if (l == NULL) {
		 l = paux;
         l->psig = NULL;


       }
       else {

        paux->psig = l;
        l = paux;
    }
   }
    return (paux);
}


struct nodo3* l_int_primero_pc(struct nodo3 *l)
{

    return (l);
}


struct nodo3* l_int_ultimo_pc(struct nodo3 *l)
{
    struct nodo3 *paux;    /*El �ltimo elemento de la lista es NULL.*/
    paux = l;
    while (paux->psig != NULL)
        paux = paux->psig;
    return (paux);
}


struct nodo3* l_int_siguiente_pc(struct nodo3 *l, struct nodo3 *pindice)
{

    return (pindice->psig);
}

struct nodo3* l_int_anterior_pc(struct nodo3 *l, struct nodo3 *pindice)
{
    struct nodo3 *paux;
    if ((pindice == l) || (l == NULL)) return(NULL);
    else {
      paux = l;
      while (paux->psig != pindice)
        paux=paux->psig;
      return (paux);
   }
}

int l_int_longitud_pc(struct nodo3 *l)
{
    int contador;
    struct nodo3 *paux;
    paux = l;
    contador = 1;
    if (paux->psig == NULL) system("PAUSE");
    while (paux->psig != NULL) {

        contador++;
        paux = paux->psig;
    }
    return (contador);
}

struct nodo3* l_int_localizar_pc_clave(struct nodo3 *l, char *clave) {
    struct nodo3* paux = l;
    while (paux != NULL) {
        if (strcmp(paux->n->clave, clave) == 0) { // Use strcmp to compare strings
            return paux;
        }
        paux = paux->psig;
    }
    return NULL; // If the node with the given key is not found
}

struct nodo3* l_int_localizar_pc_ident(struct nodo3 *l, char *ident) {
    struct nodo3* paux = l;
    while (paux != NULL) {
        if (strcmp(paux->n->ident, ident) == 0) { // Use strcmp to compare strings
            return paux;
        }
        paux = paux->psig;
    }
    return NULL; // If the node with the given key is not found
}

struct tema *l_int_elemento_pc(struct nodo3 *pindice)
{
    return (pindice->n);
}

struct nodo3* l_int_borrar_pc(struct nodo3 *l, struct nodo3 *pindice) {
    struct nodo3 *paux;
    if (l == pindice) {
        l = pindice->psig;
        free(pindice->n->clave);
        free(pindice->n->nombre);
        free(pindice->n->ano_celebracion);
        free(pindice->n->num_equipos);
        for (int i = 0; i < *(pindice->n->num_equipos); i++) {
            free(pindice->n->equipos[i]);
        }
        free(pindice->n->equipos);
        free(pindice->n->ident);
        free(pindice->n);
        free(pindice);
    } else {
        paux = l_int_anterior_pc(l, pindice);
        paux->psig = pindice->psig;
        free(pindice->n->clave);
        free(pindice->n->nombre);
        free(pindice->n->ano_celebracion);
        free(pindice->n->num_equipos);
        for (int i = 0; i < *(pindice->n->num_equipos); i++) {
            free(pindice->n->equipos[i]);
        }
        free(pindice->n->equipos);
        free(pindice->n->ident);
        free(pindice->n);
        free(pindice);
    }
    return l;
}

void imprimir_prueba_ciclista(struct pruebaCiclista *prueba) {
    printf("Clave de la prueba: %s\n", prueba->clave);
    printf("Nombre de la prueba: %s\n", prueba->nombre);
    printf("A&co de celebraci%cn: %d\n",164 ,162,prueba->ano_celebracion);
    printf("N%cmero de equipos: %d\n",163 ,prueba->num_equipos);
    printf("Equipos participantes:\n");
    for (int i = 0; i < prueba->num_equipos; i++) {
        printf("- %s\n", prueba->equipos[i]);
    }
    printf("Identificador de la prueba: %s\n", prueba->ident);
}

// Listar todas las pruebas ciclistas
void listar_pruebas(Listapc lista_pruebas) {
    if (lista_pruebas == NULL) {
        printf("No hay pruebas ciclistas registradas.\n");
        return;
    }

    struct nodo3 *actual = lista_pruebas;
    while (actual != NULL) {
        imprimir_prueba_ciclista(actual->n);
        actual = actual->psig;
    }
}
