#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include "estructuras.h"
#include "funciones.c"

bool validar_ciclista(char *nombre, struct ciclista *ciclistas, int num_ciclistas);
struct ciclista *alta_ciclistas(const char *nombre_archivo, int *clcontador);
struct pruebaCiclista *alta_prueba_ciclista(struct pruebaCiclista *p, int *contador);
struct pruebaCiclista *baja_prueba_ident(struct pruebaCiclista *p, int *contador);
struct pruebaCiclista *baja_prueba_clave(struct pruebaCiclista *p, int *contador);
struct equipo *alta_equipo(struct equipo *e, int *econtador);
struct equipo *baja_equipo(struct equipo *e, int *econtador);
struct pruebaCiclista *leer_fichero(char *nombre_fichero, int *contador);
void listar_datos(struct ciclista *ciclistas, int num_ciclistas);

#endif // FUNCIONES_H_INCLUDED
