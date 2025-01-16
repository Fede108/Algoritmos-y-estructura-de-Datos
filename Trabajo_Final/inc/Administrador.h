#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H
#include <iostream>
using namespace std;
#include "Router.h"
#include <vector>

class Grafo
{
private:
    int N; 
    int **matriz;
    int **pesos;
    int **cf;
    int **A;
    vector<Router*> nodos;
    Router* nodo;
public:
    Grafo(int N, int K);
    ~Grafo();
    void agregarArco(int n, int m);
    void mostrarGrafo();    
    void matrizPesos();
    void Floyd();
};

class Administrador
{
private:
    /* data */
public:
    Administrador(/* args */);
    ~Administrador();
    void crearGrafo(int n, int k);
};

#endif