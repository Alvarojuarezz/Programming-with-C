#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#endif // ESTRUCTURAS_H_INCLUDED
