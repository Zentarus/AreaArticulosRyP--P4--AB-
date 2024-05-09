/*//A c++ Program to implement a binary tree in data structures

#include <stdio.h>
#include "arbol.hh"

using namespace std;


string vector_articulos_a_string(vector<Articulo> articulos){
    string res = "";

    for(auto& art : articulos){
        res += art.id;
        res += ", ";
    }
}


void print_tree(int tab)
{
    //Check if tree is empty
    if(this == NULL)
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

int main(){}
*/