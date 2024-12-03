#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

#include "definiciones.h"


//FUNCIONES LISTA EQUIPO

struct nodo2* l_int_crear_e(void);
struct nodo2* l_int_insertar_e(struct nodo2 *l, struct nodo2 *pindice, struct equipo *n);
struct nodo2* l_int_inser_ppo_e(struct nodo2 *l, struct equipo *n);
struct nodo2* l_int_primero_e(struct nodo2 *l);
struct nodo2* l_int_ultimo_e(struct nodo2 *l);
struct nodo2* l_int_siguiente_e(struct nodo2 *l, struct nodo2 *pindice);
struct nodo2* l_int_anterior_e(struct nodo2 *l, struct nodo2 *pindice);
int l_int_longitud_e(struct nodo2 *l);
struct nodo2* l_int_localizar_e(struct nodo2 *l, char *clave);
struct equipo *l_int_elemento_e(struct nodo2 *pindice);
struct nodo2* l_int_borrar_e(struct nodo2 *l, struct nodo2 *pindice);
void imprimir_equipo(struct equipo *equipo);
void listar_equipos(Listae ae);

//FUNCIONES LISTA PRUEBA CICLISTA

struct nodo3* l_int_crear_pc(void);
struct nodo3* l_int_insertar_pc(struct nodo3 *l, struct nodo3 *pindice, struct pruebaCiclista *n);
struct nodo3* l_int_inser_ppo_pc(struct nodo3 *l, struct pruebaCiclista *n);
struct nodo3* l_int_primero_pc(struct nodo3 *l);
struct nodo3* l_int_ultimo_pc(struct nodo3 *l);
struct nodo3* l_int_siguiente_pc(struct nodo3 *l, struct nodo3 *pindice);
struct nodo3* l_int_anterior_pc(struct nodo3 *l, struct nodo3 *pindice);
int l_int_longitud_pc(struct nodo3 *l);
struct nodo3* l_int_localizar_pc_clave(struct nodo3 *l, char *clave);
struct nodo3* l_int_localizar_pc_ident(struct nodo3 *l, char *ident);
struct tema *l_int_elemento_pc(struct nodo3 *pindice);
struct nodo3* l_int_borrar_pc(struct nodo3 *l, struct nodo3 *pindice);
void listar_pruebas(Listapc lista_pruebas);
void imprimir_prueba_ciclista(struct pruebaCiclista *prueba);
//void listar_pc(nodo3 a);


#endif // LISTAS_H_INCLUDED
