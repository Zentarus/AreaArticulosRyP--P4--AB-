#pragma once
#include <iostream>
#include <vector>
#include "articulo.hh"

using namespace std;

class Node {
    public:
        string id;
        vector<Articulo> articulos;
        int area_pagina;
        int area_sin_ocupar; // f(x)
        int f_estim;
        int nivel;
        Node* left;
        Node* right;

        // A constructor to the struct node
        // that inserts value in the data variable.

        Node(vector<Articulo> _articulos, string _id, int _area_pagina)
        {
            id = _id;
            area_pagina = _area_pagina;
            articulos = _articulos;
            f_estim = 0;
            nivel = 0;
            left = NULL;//Left child is initialized to NULL
            right = NULL;//Right child is initialized to NULL

            int total = 0;
            for (auto& articulo : articulos){
                total += articulo.area;
            }
            area_sin_ocupar = area_pagina - total; 
        }

        static void print_tree(Node* root, int tab){
            //Check if tree is empty
            if(root == NULL)
            return;

            for(int i = 0; i < tab; i++){
                cout << "\t";
            }

            cout << "Raiz: " << root -> id << "\n";
            for(int i = 0; i < tab; i++){
                cout << "\t";
            }

            cout << "Izquierda: ";
            if(root->left != NULL){
                cout << "\n";
                print_tree(root -> left, tab+1);
            } else {
                cout << "NULL";
            }
            
            cout << "\n";
            for(int i = 0; i < tab; i++){
                cout << "\t";
            }

            cout << "Derecha: ";
            if(root->right != NULL){
                cout << "\n";
                print_tree(root -> right, tab+1);
            } else {
                cout << "NULL";
            }
        }
};



