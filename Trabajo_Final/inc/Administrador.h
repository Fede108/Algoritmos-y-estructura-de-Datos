#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H
#include <iostream>
using namespace std;
#include "Router.h"
#include <vector>

class Grafo
{
private:
    int **matriz;
    int **pesos;
    int **cf;
    int **A;
    Router* nodo;
public:
      int N; 
    vector<Router*> nodos;
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
    Grafo *grafo;
public:
    void crearGrafo(int n, int k);
    int** obtenerMatriz();
    vector<Router*> obtenerLista();
    void simular();
};

#endif