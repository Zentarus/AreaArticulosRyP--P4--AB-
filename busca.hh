#ifndef BUSCA_HH
#define BUSCA_HH

#include <vector>
#include <iostream>
#include <string>
#include "./librerias/pagina.hh"
#include "./librerias/articulo.hh"
#include <queue>

using namespace std;

struct CompareNodes {
    bool operator()(const Node& ln, const Node& rn) {
        // Ordenar por el segundo elemento de cada par (int)
        return ln.f_estim > rn.f_estim or ((ln.f_estim == rn.f_estim) and (ln.id > rn.id));
    }
};

void abrir_fichero_lectura(string nombre_fichero, ifstream& f_in);

void abrir_fichero_escritura(string nombre_fichero, ofstream& f_out);

void escribir_resultados(ofstream& f_out, double tiempo_ejecucion);

void leer_pagina(ifstream& f_in, Pagina& pagina);

void copiar_articulos(vector<Articulo> viejo, vector<Articulo> nuevo);

int calcular_area(const vector<Articulo>& articulos_actuales);

bool hay_interseccion_con_ultimo_anadido(const vector<Articulo>& articulos_actuales, int nivel);

bool aplicar_poda(const Pagina& pagina, const vector<Articulo>& articulos_actuales, const Articulo& sig_articulo, int nivel, int area_optima);

void obtener_composicion_optima(Pagina& pagina, double& duracion_ms);

#endif