#ifndef ARBOLES_H_INCLUDED
#define ARBOLES_H_INCLUDED


//LIBRERÍAS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//DEFINIMOS LAS ESTRUCTURAS

struct equipo {
    char *ident;
    char *nombre;
    int *num_corredores;
    char **ciclistas;
    char **patrocinadores;
    int *num_patroc;
};

struct pruebaCiclista {
    char *clave;
    char *nombre;
    int *ano_celebracion;
    int *num_equipos;
    char **equipos;
    char *ident;
};

//DEFINIMOS LOS NODOS DE LOS ARBOLES

typedef struct nodo_arbol_e
{
    //int valor;                       /* Campo donde almacenaremos el valor */
    struct equipo *e;
    struct nodo_arbol *izq;    /* Puntero al hijo izquierdo */
    struct nodo_arbol *der;      /* Puntero al hijo derecho */
}NODO_ARBOL_EQUIPO, *P_NODO_ARBOL_EQUIPO;

typedef struct nodo_arbol_pc
{
    //int valor;                       /* Campo donde almacenaremos el valor */
    struct pruebaCiclista *e;
    struct nodo_arbol *izq;    /* Puntero al hijo izquierdo */
    struct nodo_arbol *der;      /* Puntero al hijo derecho */
}NODO_ARBOL_PRUEBA, *P_NODO_ARBOL_PRUEBA;

//FUNCIONES ARBOL EQUIPOS

P_NODO_ARBOL_EQUIPO crearArbol_e();
int esVacio_e(P_NODO_ARBOL_EQUIPO a);
int pertenece_e(P_NODO_ARBOL_EQUIPO arbol, char *palabra);
P_NODO_ARBOL_EQUIPO encontrar_e(P_NODO_ARBOL_EQUIPO arbol, char *identificador);
P_NODO_ARBOL_EQUIPO padre_de_e(P_NODO_ARBOL_EQUIPO arbol, P_NODO_ARBOL_EQUIPO nodo);
P_NODO_ARBOL_EQUIPO insertar_e(P_NODO_ARBOL_EQUIPO arbol, struct equipo *equipo);
P_NODO_ARBOL_EQUIPO eliminar_e(P_NODO_ARBOL_EQUIPO a, char *identificador);
char *mostrar_nodo_e(P_NODO_ARBOL_EQUIPO a);
void preOrder_e(P_NODO_ARBOL_EQUIPO a);
void postOrder_e(P_NODO_ARBOL_EQUIPO a);
void inOrder_e(P_NODO_ARBOL_EQUIPO a);

//FUNCIONES ARBOL PRUEBAS CICLISTA

P_NODO_ARBOL_PRUEBA crearArbol_pc();
int esVacio_pc(P_NODO_ARBOL_PRUEBA a);
P_NODO_ARBOL_PRUEBA alojar_nodo_arbol_pc();
int pertenece_pc(P_NODO_ARBOL_PRUEBA arbol, char *palabra);
P_NODO_ARBOL_PRUEBA encontrar_pc_clave(P_NODO_ARBOL_PRUEBA arbol, char *clave);
P_NODO_ARBOL_PRUEBA encontrar_pc_ident(P_NODO_ARBOL_PRUEBA arbol, char *identificador);
P_NODO_ARBOL_PRUEBA padre_de_pc(P_NODO_ARBOL_PRUEBA arbol, P_NODO_ARBOL_PRUEBA nodo);
P_NODO_ARBOL_PRUEBA insertar_pc(P_NODO_ARBOL_PRUEBA arbol, struct pruebaCiclista *prueba);
P_NODO_ARBOL_PRUEBA borraNodo_pc(P_NODO_ARBOL_PRUEBA nodo);
P_NODO_ARBOL_PRUEBA eliminar_pc_ident(P_NODO_ARBOL_PRUEBA a, char *identificador);
P_NODO_ARBOL_PRUEBA eliminar_pc_clave(P_NODO_ARBOL_PRUEBA a, char *clave);
void postOrder_pc(P_NODO_ARBOL_PRUEBA a);
void preOrder_pc(P_NODO_ARBOL_PRUEBA a);
void inOrder_pc(P_NODO_ARBOL_PRUEBA a);

#endif // ARBOLES_H_INCLUDED
