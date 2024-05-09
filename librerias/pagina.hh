#pragma once
#include <vector>
#include <iostream>
#include "articulo.hh"

using namespace std;

class Pagina {
public:
    int num_articulos;
    int ancho;
    int alto;
    int area;
    vector<Articulo> articulos; 

    Pagina(int _num_articulos, int _ancho, int _alto, const vector<Articulo>& _articulos) :
        num_articulos(_num_articulos), ancho(_ancho), alto(_alto), articulos(_articulos) {
            area = _ancho * _alto;
    }

    Pagina() :
        Pagina(0, 0, 0, vector<Articulo>()) {}

    void actualizar_area(){
        area = ancho * alto;
    }

    void mostrar_pagina(bool mostrar_articulos, int num_pagina = 0){
        cout << endl;
        cout << "Pagina " << num_pagina << ":" << endl;
        cout << "----------------------------------" << endl;
        cout << "num_articulos -> " << num_articulos << endl;
        cout << "alto -> " << alto << endl;
        cout << "ancho -> " << ancho << endl;
        cout << "area -> " << area << endl << endl;
        if(mostrar_articulos){
            for(int i = 0; i < num_articulos; i++){
                articulos[i].mostrar_articulo();
                cout << endl;
            }
        }
    }
};
