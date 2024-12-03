#include "arboles.h"
#include "prueba.h"

/* Crea un arbol vacio*/
P_NODO_ARBOL_PRUEBA crearArbol_pc()
{
	return NULL;
}
/* Devuelve 1 si el arbol esta vacio*/
int esVacio_pc(P_NODO_ARBOL_PRUEBA a)
{
	return (a==NULL);
}

P_NODO_ARBOL_PRUEBA alojar_nodo_arbol_pc()
{
    return((P_NODO_ARBOL_PRUEBA)malloc(sizeof(NODO_ARBOL_PRUEBA))); /* Reservamos memoria */
}

int pertenece_pc(P_NODO_ARBOL_PRUEBA arbol, char *palabra)
{
    if (arbol == NULL)    /* Si el ·rbol est· vacio */
        return (0);

    int comparar = strcmp(arbol->e, palabra);

    if (comparar == 0)    /* Hemos encontrado el valor */
        return (1);           /* Devuelve 1 para evaluarlo en el main */
    if (comparar > 0) /* En el arbol los menores est·n a la izquierda
                           y los mayores a la derecha. Por tanto, si
                           i es menor que el valor actual tendremos que
                           ir hacia la izquierda */
        return (pertenece_pc(arbol->izq, palabra));
    else     /* "i" es mayor que el valor actual */
        return (pertenece_pc(arbol->der, palabra));
}

P_NODO_ARBOL_PRUEBA encontrar_pc_ident(P_NODO_ARBOL_PRUEBA arbol, char *identificador)
{
    if (arbol == NULL)    /* Arbol vacÌo por tanto devuelve NULL */
        return (NULL);
    int comparar = strcmp(arbol->e->ident, identificador);

    if (comparar == 0)     /* Hemos encontrado el valor */
        return (arbol);
    else if (comparar > 0)    /* El valor actual es mayor que ir por tanto
                                   vamos hacia la izquierda */
        return(encontrar_pc_ident(arbol->izq, identificador));
    else    /* "i" es mayor que el valor actual */
        return(encontrar_pc_ident(arbol->der, identificador));
}

P_NODO_ARBOL_PRUEBA encontrar_pc_clave(P_NODO_ARBOL_PRUEBA arbol, char *clave)
{
    if (arbol == NULL)    /* Arbol vacÌo por tanto devuelve NULL */
        return (NULL);
    int comparar = strcmp(arbol->e->clave, clave);

    if (comparar == 0)     /* Hemos encontrado el valor */
        return (arbol);
    else if (comparar > 0)    /* El valor actual es mayor que ir por tanto
                                   vamos hacia la izquierda */
        return(encontrar_pc_clave(arbol->izq, clave));
    else    /* "i" es mayor que el valor actual */
        return(encontrar_pc_clave(arbol->der, clave));
}

P_NODO_ARBOL_PRUEBA padre_de_pc(P_NODO_ARBOL_PRUEBA arbol, P_NODO_ARBOL_PRUEBA nodo)
{
    if (arbol == NULL)    /* Arbol vacÌo por tanto devuelve NULL */
        return (NULL);
    int comparar = strcmp(arbol->e, nodo->e);
    if (arbol->izq == nodo || arbol->der == nodo) /* Encontrado */
        return (arbol);
    else if (comparar > 0) /* El elemento a buscar es menor que
                                          el elemento actual del arbol por
                                          tanto vamos a la izquierda */
        return(padre_de_pc(arbol->izq, nodo));
    else    /* El elemento a buscar es mayor que el elemento actual */
        return(padre_de_pc(arbol->der, nodo));
}

P_NODO_ARBOL_PRUEBA insertar_pc(P_NODO_ARBOL_PRUEBA arbol, struct pruebaCiclista *prueba)
{
    P_NODO_ARBOL_PRUEBA p;    /* Para no perder la cabeza del arbol */

    if (arbol == NULL)
    {
        p = alojar_nodo_arbol_pc();             /* Reservamos memoria */
        p->izq = p->der = NULL;             /* Acabamos de crearlo */
        p->e = prueba;
        return (p);
    }
    int comparar = strcmp(arbol->e->ident, prueba->ident);
    if (comparar == 0)    /* El valor ya existe. No hacemos nada porque no
                               permitimos valores duplicados */
        return (arbol);

    if (comparar > 0) /* "i" es menor que el valor que analizo, por tanto,
                           inserto a la izquierda */
        arbol->izq = insertar_pc(arbol->izq, prueba);
    else  /* "i" es mayor que el valor actual, entonces, inserto a la derecha */
        arbol->der = insertar_pc(arbol->der, prueba);

    return (arbol);
}


P_NODO_ARBOL_PRUEBA borraNodo_pc(P_NODO_ARBOL_PRUEBA nodo)
{
    free(nodo->e->ident);
    free(nodo->e->nombre);
    free(nodo->e->ano_celebracion);
    free(nodo->e->num_equipos);
    for (int i = 0; i < *(nodo->e->num_equipos); i++) {
        free(nodo->e->equipos[i]);
    }
    free(nodo->e->equipos);
    free(nodo->e);

    free(nodo);

    return NULL;
}

P_NODO_ARBOL_PRUEBA eliminar_pc_ident(P_NODO_ARBOL_PRUEBA a, char *identificador)
{
    if (a == NULL) return a;

    int comparar = strcmp(a->e->ident, identificador);

    if (comparar > 0) a->izq = eliminar_pc_ident(a->izq, identificador);
    else if (comparar < 0) a->der = eliminar_pc_ident(a->der, identificador);
    else{
        if ((a->der == NULL)&&(a->izq == NULL)) //caso 1
            return borraNodo_pc(a);
        //Caso 2
        if (a->der == NULL){
            P_NODO_ARBOL_PRUEBA q = a->izq;
            borraNodo_pc(a);
            return q;
        }
        if (a->izq == NULL){
            P_NODO_ARBOL_PRUEBA q = a->der;
            borraNodo_pc(a);
            return q;
        }
        //Caso 3
        P_NODO_ARBOL_PRUEBA q, p;
        for(p=a,q=a->izq; q->der != NULL; q = q->der)
            p=q;
        if (p!=a)
            p->der = q->izq;
        else
            p->izq = q->izq;
        a->e = q->e;
        borraNodo_pc(q);
    }
    return a;
}

P_NODO_ARBOL_PRUEBA eliminar_pc_clave(P_NODO_ARBOL_PRUEBA a, char *clave)
{
    P_NODO_ARBOL_PRUEBA q, p;

    if (a == NULL)
        return a;

    int comparar = strcmp(a->e->clave, clave);

    if (comparar > 0)
        a->izq = eliminar_pc_clave(a->izq, clave);
    else if (comparar < 0)
        a->der = eliminar_pc_clave(a->der, clave);
    else {
        if ((a->der == NULL) && (a->izq == NULL)) // caso 1
            return borraNodo_pc(a);

        // caso 2
        if (a->der == NULL) {
            q = a->izq;
            borraNodo_pc(a);
            return q;
        }
        if (a->izq == NULL) {
            q = a->der;
            borraNodo_pc(a);
            return q;
        }
        // caso 3
        for (p = a, q = a->izq; q->der != NULL; q = q->der)
            p = q;

        if (p != a)
            p->der = q->izq;
        else
            p->izq = q->izq;

        a->e = q->e;
        borraNodo_pc(q);
    }
    return a;
}


void postOrder_pc(P_NODO_ARBOL_PRUEBA a)//Posterior
{
	if (!esVacio_pc(a))
	{
		postOrder_pc(a->izq);
		postOrder_pc(a->der);
        mostrar_prueba(a);
    }

}

void preOrder_pc(P_NODO_ARBOL_PRUEBA a)//Previo 1ºder 100
{
	if (!esVacio_pc(a))
	{

        mostrar_prueba(a);
		preOrder_pc(a->izq);
		preOrder_pc(a->der);
	}

}

void inOrder_pc(P_NODO_ARBOL_PRUEBA a)//Simetrico
{
	if (!esVacio_pc(a))
	{
  		inOrder_pc(a->izq);
  		mostrar_prueba(a);
  		inOrder_pc(a->der);
	}
}
