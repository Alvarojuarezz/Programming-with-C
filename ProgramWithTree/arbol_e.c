#include "arboles.h"
#include "equipo.h"

/*Crea un arbol vacio*/
P_NODO_ARBOL_EQUIPO crearArbol_e()
{
	return NULL;
}

/* Devuelve 1 si el arbol esta vacio*/
int esVacio_e(P_NODO_ARBOL_EQUIPO a)
{
	return (a==NULL);
}

P_NODO_ARBOL_EQUIPO alojar_nodo_arbol_e()
{
    return((P_NODO_ARBOL_EQUIPO)malloc(sizeof(NODO_ARBOL_EQUIPO))); /* Reservamos memoria */
}


int pertenece_e(P_NODO_ARBOL_EQUIPO arbol, char *palabra)
{
    /* Devuelve verdadero si el valor "i" se encuentra en el arbol "arbol", y falso
    en caso contrario */
    if (arbol == NULL)    /* Si el ·rbol est· vacio */
        return (0);

    int comparar = strcmp(arbol->e, palabra);

    if (comparar == 0)    /* Hemos encontrado el valor */
        return (1);           /* Devuelve 1 para evaluarlo en el main */
    if (comparar > 0) /* En el arbol los menores est·n a la izquierda
                           y los mayores a la derecha. Por tanto, si
                           i es menor que el valor actual tendremos que
                           ir hacia la izquierda */
        return (pertenece_e(arbol->izq, palabra));
    else     /* "i" es mayor que el valor actual */
        return (pertenece_e(arbol->der, palabra));
}

P_NODO_ARBOL_EQUIPO encontrar_e(P_NODO_ARBOL_EQUIPO arbol, char *identificador)
{
    if (arbol == NULL)    /* Arbol vacío, por tanto devuelve NULL */
        return NULL;

    int comparar = strcmp(arbol->e->ident, identificador);

    if (comparar == 0)     /* Hemos encontrado el valor */
        return arbol;
    else if (comparar > 0)    /* El identificador actual es mayor que el identificador buscado, por tanto, vamos hacia la izquierda */
        return encontrar_e(arbol->izq, identificador);
    else    /* El identificador actual es menor que el identificador buscado, por tanto, vamos hacia la derecha */
        return encontrar_e(arbol->der, identificador);
}

P_NODO_ARBOL_EQUIPO padre_de_e(P_NODO_ARBOL_EQUIPO arbol, P_NODO_ARBOL_EQUIPO nodo)

{
    if (arbol == NULL)    /* Arbol vacÌo por tanto devuelve NULL */
        return (NULL);
    int comparar = strcmp(arbol->e, nodo->e);
    if (arbol->izq == nodo || arbol->der == nodo) /* Encontrado */
        return (arbol);
    else if (comparar > 0) /* El elemento a buscar es menor que
                                          el elemento actual del arbol por
                                          tanto vamos a la izquierda */
        return(padre_de_e(arbol->izq, nodo));
    else    /* El elemento a buscar es mayor que el elemento actual */
        return(padre_de_e(arbol->der, nodo));
}

P_NODO_ARBOL_EQUIPO insertar_e(P_NODO_ARBOL_EQUIPO arbol, struct equipo *equipo)
{
    P_NODO_ARBOL_EQUIPO p;

    if (arbol == NULL)
    {
        p = alojar_nodo_arbol_e();
        p->izq = p->der = NULL;
        p->e = equipo; // Asigna el puntero al equipo
        return p;
    }
    int comparar = strcmp(arbol->e->ident, equipo->ident); // Compara los identificadores
    if (comparar == 0)
        return arbol;

    if (comparar > 0)
        arbol->izq = insertar_e(arbol->izq, equipo);
    else
        arbol->der = insertar_e(arbol->der, equipo);

    return arbol;
}

P_NODO_ARBOL_EQUIPO borraNodo_e(P_NODO_ARBOL_EQUIPO nodo)
{
    if (nodo != NULL) {
        free(nodo->e->ident);
        free(nodo->e->nombre);
        free(nodo->e->num_corredores);
        free(nodo->e->ciclistas);
        free(nodo->e->num_patroc);
        free(nodo->e->patrocinadores);
        free(nodo->e);
        free(nodo);
    }
    return NULL;
}



P_NODO_ARBOL_EQUIPO eliminar_e(P_NODO_ARBOL_EQUIPO a, char *identificador)
{
    if (a == NULL) return a;

    int comparar = strcmp(a->e->ident, identificador);

    if (comparar > 0)
        a->izq = eliminar_e(a->izq, identificador);
    else if (comparar < 0)
        a->der = eliminar_e(a->der, identificador);
    else {
        if (a->der == NULL && a->izq == NULL) { // caso 1: nodo sin hijos
            return borraNodo_e(a);
        } else if (a->der == NULL) { // caso 2: nodo con un hijo izquierdo
            P_NODO_ARBOL_EQUIPO temp = a->izq;
            borraNodo_e(a);
            return temp;
        } else if (a->izq == NULL) { // caso 2: nodo con un hijo derecho
            P_NODO_ARBOL_EQUIPO temp = a->der;
            borraNodo_e(a);
            return temp;
        } else { // caso 3: nodo con dos hijos
            // Encuentra el sucesor inmediato en el subárbol derecho
            P_NODO_ARBOL_EQUIPO sucesor = a->der;
            while (sucesor->izq != NULL) {
                sucesor = sucesor->izq;
            }
            // Copia el contenido del sucesor al nodo actual
            a->e = sucesor->e;
            // Elimina el sucesor del subárbol derecho
            a->der = eliminar_e(a->der, sucesor->e->ident);
        }
    }
    return a;
}

void postOrder_e(P_NODO_ARBOL_EQUIPO a) //Posterior
{
    if (!esVacio_e(a)) {
        postOrder_e(a->izq);
        postOrder_e(a->der);
        mostrar_equipo(a);
    }
}

void preOrder_e(P_NODO_ARBOL_EQUIPO a) //Previo 1ºder 100
{
    if (!esVacio_e(a)) {
        mostrar_equipo(a);
        preOrder_e(a->izq);
        preOrder_e(a->der);
    }
}

void inOrder_e(P_NODO_ARBOL_EQUIPO a) //Simetrico
{
    if (!esVacio_e(a)) {
        inOrder_e(a->izq);
        mostrar_equipo(a);
        inOrder_e(a->der);
    }
}


char *mostrar_nodo_e(P_NODO_ARBOL_EQUIPO a)
{
    return (a->e);
}
