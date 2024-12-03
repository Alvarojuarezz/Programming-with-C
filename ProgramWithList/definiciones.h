#ifndef DEFINICIONES_H_INCLUDED
#define DEFINICIONES_H_INCLUDED

//LIBRERIAS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ESTRUCTURAS

struct ciclista {
    char *nombre;
    int *ano_prof;
};

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

//NODOS
struct nodo1
{
    struct ciclista *n;
    struct nodo1 *psig;
};

typedef struct nodo1 *Listac;
typedef struct nodo1 *Posicionc;

struct nodo2
{
    struct equipo *n;
    struct nodo2 *psig;
};

typedef struct nodo2 *Listae;
typedef struct nodo2 *Posicione;

struct nodo3
{
    struct pruebaCiclista *n;
    struct nodo3 *psig;
};

typedef struct nodo3 *Listapc;
typedef struct nodo3 *Posicionpc;

#endif // DEFINICIONES_H_INCLUDED
