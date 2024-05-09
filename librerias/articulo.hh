#pragma once
#include <iostream>

using namespace std;

class Articulo {
public:
    int id;
    int x;
    int y;
    int ancho;
    int alto;
    int area;

    Articulo(int _id, int _ancho, int _alto, int _x, int _y) :
        id(_id), ancho(_ancho), alto(_alto), x(_x), y(_y) {
            area = _ancho * _alto;
        }

    Articulo() :
        id(0), ancho(0), alto(0), x(0), y(0), area(0) {}

    void mostrar_articulo(){
        cout << "Articulo " + id << ":" << endl;
        cout << "-----------------" << endl;
        cout << "ancho -> " << ancho << endl;
        cout << "alto -> " << alto << endl;
        cout << "x -> " << x << endl;
        cout << "y -> " << y << endl;
        cout << "area -> " << area << endl;
    }

    friend bool operator==(const Articulo& a, const Articulo& b){
        return a.id == b.id;
    }

    friend bool operator<(const Articulo& a, const Articulo& b){
        return a.id < b.id;
    }
};