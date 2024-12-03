#include "listas.h"


struct nodo2* l_int_crear_e(void)
{
   return (NULL);
}

struct nodo2* l_int_insertar_e(struct nodo2 *l, struct nodo2 *pindice, struct equipo *n)
{
    struct nodo2 *paux;
    paux = (struct nodo2 *) malloc(sizeof(struct nodo2));
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



struct nodo2* l_int_inser_ppo_e(struct nodo2 *l, struct equipo *n)
{
    struct nodo2 *paux;

    paux = (struct nodo2 *) malloc(sizeof (struct nodo2));

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


struct nodo2* l_int_primero_e(struct nodo2 *l)
{

    return (l);
}


struct nodo2* l_int_ultimo_e(struct nodo2 *l)
{
    struct nodo2 *paux;    /*El �ltimo elemento de la lista es NULL.*/
    paux = l;
    while (paux->psig != NULL)
        paux = paux->psig;
    return (paux);
}


struct nodo2* l_int_siguiente_e(struct nodo2 *l, struct nodo2 *pindice)
{

    return (pindice->psig);
}

struct nodo2* l_int_anterior_e(struct nodo2 *l, struct nodo2 *pindice)
{
    struct nodo2 *paux;
    if ((pindice == l) || (l == NULL)) return(NULL);
    else {
      paux = l;
      while (paux->psig != pindice)
        paux=paux->psig;
      return (paux);
   }
}

int l_int_longitud_e(struct nodo2 *l)
{
    int contador;
    struct nodo2 *paux;
    paux = l;
    contador = 1;
    if (paux->psig == NULL) system("PAUSE");
    while (paux->psig != NULL) {

        contador++;
        paux = paux->psig;
    }
    return (contador);
}


struct nodo2* l_int_localizar_e(struct nodo2 *l, char *ident) {
    struct nodo2* paux = l;
    while (paux != NULL) {
        if (strcmp(ident, paux->n->ident) == 0) {
            return paux;
        }
        paux = paux->psig;
    }
    return NULL;
}




struct equipo *l_int_elemento_e(struct nodo2 *pindice)
{
    return (pindice->n);
}

struct nodo2* l_int_borrar_e(struct nodo2 *l, struct nodo2 *pindice) {
    if (pindice == NULL) {
        printf("Error: Intento de borrar un nodo nulo.\n");
        return l;
    }

    struct nodo2 *paux;
    if (l == pindice) {
        l = pindice->psig;
        free(pindice->n->ident);
        free(pindice->n->nombre);
        free(pindice->n->ciclistas);
        free(pindice->n->patrocinadores);
        free(pindice->n->num_corredores);
        free(pindice->n->num_patroc);
        free(pindice->n);
        free(pindice);
    } else {
        paux = l_int_anterior_e(l, pindice);
        paux->psig = pindice->psig;
        free(pindice->n->ident);
        free(pindice->n->nombre);
        free(pindice->n->ciclistas);
        free(pindice->n->patrocinadores);
        free(pindice->n->num_corredores);
        free(pindice->n->num_patroc);
        free(pindice->n);
        free(pindice);
    }
    return l;
}

void imprimir_equipo(struct equipo *equipo) {
    printf("Identificador del equipo: %s\n", equipo->ident);
    printf("Nombre del equipo: %s\n", equipo->nombre);
    printf("N%cmero de corredores: %d\n", 163,equipo->num_corredores);
    printf("Ciclistas:\n");
    for (int i = 0; i < equipo->num_corredores; i++) {
        printf("- %s\n", equipo->ciclistas[i]);
    }
    printf("N%cmero de patrocinadores: %d\n",163, equipo->num_patroc);
    printf("Patrocinadores:\n");
    for (int i = 0; i < equipo->num_patroc; i++) {
        printf("- %s\n", equipo->patrocinadores[i]);
    }
}

void listar_equipos(Listae ae) {
    if (ae == NULL) {
        printf("No hay equipos dados de alta.\n");
        return;
    }
    struct nodo2 *actual = ae;
    while (actual != NULL) {
        imprimir_equipo(actual->n);
        actual = actual->psig;
    }
}



