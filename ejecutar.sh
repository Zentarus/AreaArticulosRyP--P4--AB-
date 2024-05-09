#!/bin/bash

# Eliminamos ficheros de objeto y ejecutables
if [ -f busca.exe ]; then
    echo "ELIMINADO: antiguo ejecutable 'busca.exe'"
    rm busca.exe
fi

if [ -f busca.o ]; then
    echo "ELIMINADO: antiguo archivo objeto 'busca.o'"
    rm busca.o
fi

# Compilamos el programa
g++ busca.hh busca.cc -o busca -std=c++11

# Por si no existe pruebas.txt
if [ ! -f entrada.txt ]; then
    echo "AVISO: El archivo 'entrada.txt' no existe"
    exit 1
fi

# Llamar al programa busca con los archivos de entrada y salida
./busca entrada.txt salida_p2.txt