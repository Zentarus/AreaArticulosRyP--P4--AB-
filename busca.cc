#include "busca.hh"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <stdlib.h>
#include <algorithm>
#include "./librerias/arbol.hh"


using namespace std;

void abrir_fichero_lectura(string nombre_fichero, ifstream& f_in){
    f_in.open(nombre_fichero);
    if (!f_in.is_open()){
        cout << "Error al abrir el fichero \"" << nombre_fichero << "\" para su lectura" << endl;
        exit(1);
    }
}

void abrir_fichero_escritura(string nombre_fichero, ofstream& f_out){
    f_out.open(nombre_fichero);
    if (!f_out.is_open()){
        cout << "Error al abrir el fichero \"" << nombre_fichero << "\" para su escritura" << endl;
        exit(1);
    }
}

void leer_pagina(ifstream& f_in, Pagina& pagina){

    string s_num_articulos, s_ancho_pag, s_alto_pag;
    string x_articulo, y_articulo, ancho_articulo, alto_articulo;

    getline(f_in, s_num_articulos, ' ');
    getline(f_in, s_ancho_pag, ' ');
    getline(f_in, s_alto_pag);

    int num_articulos = stoi(s_num_articulos);
    int ancho_pag = stoi(s_ancho_pag);
    int alto_pag = stoi(s_alto_pag);

    vector<Articulo> v_articulos;

    for (int i = 0; i < num_articulos; i++){
        
        getline(f_in, ancho_articulo, ' ');
        getline(f_in, alto_articulo, ' ');
        getline(f_in, x_articulo, ' ');
        getline(f_in, y_articulo);

        v_articulos.push_back(Articulo(i, stoi(ancho_articulo), stoi(alto_articulo), stoi(x_articulo), stoi(y_articulo)));

    }

    pagina.num_articulos = num_articulos;
    pagina.ancho = ancho_pag;
    pagina.alto = alto_pag;
    pagina.actualizar_area();
    pagina.articulos = v_articulos;
}

void escribir_resultados(ofstream& f_out, double tiempo_ejecucion){
    f_out << "Aqui resultado area | " << setprecision(3) << tiempo_ejecucion << " ms" << endl;
}

void copiar_articulos(vector<Articulo> viejo, vector<Articulo> nuevo){
    for (auto& articulo : viejo){
        nuevo.push_back(articulo);
    }
}

void calcular_partes(const vector<Articulo>& articulos_actuales, vector<vector<Articulo>>& partes){
    for (int i = 0; i < articulos_actuales.size(); i++)
    {
        vector<Articulo> empty;
        partes.push_back( empty );

        vector< vector<Articulo> > subset_temp = partes;  //making a copy of given 2-d vector.
        
        for (int j = 0; j < subset_temp.size(); j++)
            subset_temp[j].push_back( articulos_actuales[i] );   // adding set[i] element to each subset of subsetTemp. like adding {2}(in 2nd iteration  to {{},{1}} which gives {{2},{1,2}}.
        
        for (int j = 0; j < subset_temp.size(); j++)
            partes.push_back( subset_temp[j] );  //now adding modified subsetTemp to original subset (before{{},{1}} , after{{},{1},{2},{1,2}})
    }

    sort(partes.begin(), partes.end());
    partes.erase( unique(partes.begin(), partes.end() ), partes.end());
}

bool hay_interseccion_entre_pareja_articulos(Articulo a, Articulo b){
    return  (a.x < b.x + b.ancho &&
            a.x + a.ancho > b.x &&
            a.y < b.y + b.alto &&
            a.y + a.alto > b.y);
}

bool intersecan_todos_articulos(const vector<Articulo>& articulos) {
    for(int i = 0; i < articulos.size(); i++){
        for(int j = i+1; j < articulos.size(); j++){
            if(!hay_interseccion_entre_pareja_articulos(articulos[i], articulos[j])){
                return false;
            }
        }
    }
    return true;
}

Articulo calcular_articulo_interseccion_pareja(Articulo a, Articulo b){

    // guardamos los puntos derecha-inferior de ambos articulos por comodidad
    int x_dcha_a = a.x + a.ancho;
    int y_inf_a = a.y + a.alto;

    int x_dcha_b = b.x + b.ancho;
    int y_inf_b = b.y + b.alto;

    int res_x = max(a.x, b.x);
    int res_y = max(a.y, b.y);
    int res_ancho = min(x_dcha_a, x_dcha_b) - res_x;
    int res_alto = min(y_inf_a, y_inf_b) - res_y;

    return Articulo(0, res_ancho, res_alto, res_x, res_y);
}

int calcular_area_articulos_solapados(const vector<Articulo>& articulos) {
    if(articulos.size() == 0){
        return 0;
    }
    if(articulos.size() == 1){
        return articulos[0].area;
    }

    if(!intersecan_todos_articulos(articulos)){
        return 0;
    }

    Articulo interseccion = articulos[0];
    for(int i = 1; i < articulos.size(); i++){
        interseccion = calcular_articulo_interseccion_pareja(interseccion, articulos[i]);
    }

    return interseccion.area;
}



// Calcula el área actual ocupada por los articulos pasados por parámetro
int calcular_area(const vector<Articulo>& articulos) {
    int area_total = 0;

    vector<vector<Articulo>> partes;
    calcular_partes(articulos, partes);

    for(vector<Articulo> conjunto : partes){

        int area_interseccion = calcular_area_articulos_solapados(conjunto);
        if(conjunto.size() % 2 == 0){
            area_total -= area_interseccion;
        } else {
            area_total += area_interseccion;
        }
    }

    return area_total;
}

// Comprueba si hay intersección entre el artículo actual y los articulos colocados anteriormente
bool hay_interseccion_con_sig_articulo(const vector<Articulo>& articulos_actuales, const Articulo& sig_articulo, int nivel) {
    const Articulo& articulo_actual = sig_articulo;

    for (int i = 0; i < articulos_actuales.size(); ++i) {
        const Articulo& articulo_anterior = articulos_actuales[i];
        
        // Comprueba si hay intersección entre los artículos
        if (hay_interseccion_entre_pareja_articulos(articulo_actual, articulo_anterior)) {
            return true;
        }
    }
    return false;
}

int area_restante_maxima(const Pagina& pagina, const vector<Articulo>& articulos_actuales, int nivel){
    vector<Articulo> articulos_restantes = articulos_actuales;
    for (int i = nivel; i < pagina.num_articulos; i++){
        articulos_restantes.push_back(pagina.articulos[i]);
    }

    return calcular_area(articulos_restantes);
}

bool aplicar_poda(const Pagina& pagina, const vector<Articulo>& articulos_actuales, const Articulo& sig_articulo, int nivel, int area_optima) {

    int area_restante_max = area_restante_maxima(pagina, articulos_actuales, nivel);

    if(area_optima >= area_restante_max){
        return true;
    }
    
    return false;
}

void construir_siguiente_nivel(Pagina& pagina, Node* raiz, vector<Articulo> articulos_actuales, vector<Articulo>& articulos_optimos, int& area_optima, int nivel){
    int area_actual = calcular_area(articulos_actuales);

    if(nivel == pagina.articulos.size() && area_actual > area_optima){
        area_optima = area_actual;
        articulos_optimos = articulos_actuales;
                
    } else if (nivel < pagina.articulos.size()){    // Para que en la siguiente instruccion no se acceda a una componente fuera de rango
                                                    // Tambien es la condición de poda para no pasarnos del número de articulos
        Articulo sig_articulo = pagina.articulos[nivel];
        







        if (!aplicar_poda(pagina, articulos_actuales, sig_articulo, nivel, area_optima))
        {
            if(!hay_interseccion_con_sig_articulo(articulos_actuales, sig_articulo, nivel)){
                // añade el articulo al vector
                articulos_actuales.push_back(pagina.articulos[nivel]);

                // RECORRE IZQUIERDA (añade el nuevo articulo)
                // (recorre primero izquierda porque añadir un articulo nuevo siempre sera mejor que no añadirlo)
                raiz->left = new Node(articulos_actuales, raiz->id + to_string(sig_articulo.id));
                //area_optima = max(calcular_area(pagina, articulos_actuales), area_optima);
                construir_siguiente_nivel(pagina, raiz->left, articulos_actuales, articulos_optimos, area_optima, nivel + 1);

                // extrae el articulo del vector
                articulos_actuales.pop_back();
            }

            // RECORRE DERECHA (no añade el nuevo articulo)
            raiz->right = new Node(raiz->articulos, raiz->id);
            construir_siguiente_nivel(pagina, raiz->right, articulos_actuales, articulos_optimos, area_optima, nivel + 1);
        }
    }
}


int obtener_composicion_optima(Pagina& pagina, vector<Articulo>& articulos_optimos){
    int area_optima = 0;
    vector<Articulo> articulos_insertados;
    Node* raiz = new Node(articulos_insertados, "");

    construir_siguiente_nivel(pagina, raiz, articulos_insertados, articulos_optimos, area_optima, 0);
    return area_optima;
}

void imprimir_solucion(ofstream& f_out, int num_pag, int area_solucion, vector<Articulo> art_solucion, long double tiempo_ejecucion){
    f_out << endl;

    f_out << "Pagina " << num_pag << endl << "\tTiempo: " << tiempo_ejecucion << " ms" << endl << "\tArea: " << area_solucion << " mm" << endl << "\tArticulos:";
    for(Articulo art : art_solucion){
        f_out << endl << "\t\t";
        f_out << art.ancho << " " << art.alto << " " << art.x << " " << art.y << " (Area: " << art.area << " mm)";
    }

    f_out << endl;
}

int main(int argc, char *argv[]){
    double tiempo_ejecucion = 0.0;
    ifstream f_in;
    ofstream f_out;
    int num_pag = 1;
    int area_solucion = 0;
    vector<Articulo> articulos_solucion = {};


    if (argc < 3){
        cout << "ERROR: Numero de parametros invalido" << endl;
        exit(1);
    }

    abrir_fichero_lectura(argv[1], f_in);
    abrir_fichero_escritura(argv[2], f_out);

    while(!f_in.eof()){
        Pagina pagina;
        leer_pagina(f_in, pagina);

        auto start_time = chrono::high_resolution_clock::now();
        area_solucion = obtener_composicion_optima(pagina, articulos_solucion);
        auto end_time = chrono::high_resolution_clock::now();
        
        auto duracion = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time) / 1000000.0;
        tiempo_ejecucion = duracion.count();

        imprimir_solucion(f_out, num_pag, area_solucion, articulos_solucion, tiempo_ejecucion);
        num_pag++;
    }
    
    f_in.close();
    f_out.close();
    return 0;
}