#ifndef BUSCARYP_HH
#define BUSCARYP_HH

#include <vector>
#include <iostream>
#include <string>
#include "./librerias/pagina.hh"
#include "./librerias/arbol.hh"
#include "./librerias/articulo.hh"
#include <queue>

using namespace std;

struct CompareNodes {
    bool operator()(const Node* ln, const Node* rn) {
        // Ordenar por el segundo elemento de cada par (int)
        return (ln->f_estim > rn->f_estim || ((ln->f_estim == rn->f_estim) && (ln->id > rn->id)));
    }
};

void abrir_fichero_lectura(string nombre_fichero, ifstream& f_in);
void abrir_fichero_escritura(string nombre_fichero, ofstream& f_out);
void leer_pagina(ifstream& f_in, Pagina& pagina);
void imprimir_solucion(ofstream& f_out, int num_pag, int area_solucion, vector<Articulo> art_solucion, long double tiempo_ejecucion, int nodos_expandidos);
void imprimir_solucion_por_pantalla(int num_pag, int area_solucion, vector<Articulo> art_solucion, long double tiempo_ejecucion, int nodos_expandidos);
int obtener_composicion_optima(Pagina& pagina, vector<Articulo>& articulos_optimos, int& nodos_expandidos);
bool hay_interseccion_con_sig_articulo(const vector<Articulo>& articulos_actuales, const Articulo& sig_articulo);
void expandir_nodos_hijos(Node* nodo_a_expandir, Pagina pagina, vector<Articulo> art_insertados, priority_queue<Node*, 
                          vector<Node*>, CompareNodes> &cola_nodos, int& area_minima, vector<Articulo>& articulos_optimos, int& nodos_expandidos);
void calcular_partes(const vector<Articulo>& articulos_actuales, vector<vector<Articulo>>& partes);
bool hay_interseccion_entre_pareja_articulos(Articulo a, Articulo b);
bool intersecan_todos_articulos(const vector<Articulo>& articulos);
Articulo calcular_articulo_interseccion_pareja(Articulo a, Articulo b);
int calcular_area_articulos_solapados(const vector<Articulo>& articulos);
int calcular_area(const vector<Articulo>& articulos);
int calcular_area_articulos_sin_solapar(vector<Articulo> arts_en_pagina);
int area_restante_posible_maxima(const Pagina& pagina, vector<Articulo> arts_actuales, int nivel);
int calcular_func_estimacion(Node* nodo, Pagina pagina);

#endif
