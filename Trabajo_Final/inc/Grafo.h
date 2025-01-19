#include <vector>
#ifndef GRAFO_H
#define GRAFO_H
#include "Router.h"
#include "Vector.h"

class Grafo
{
private:
    int **matriz;
    int **cf;
    int **A;
    Router* nodo;
public:
    int **pesos;
    int N; 
    vectorClass<Router*> nodos;
    Grafo(int N, int K);
    ~Grafo();
    void agregarArco(int n, int m);
    void mostrarGrafo();    
    void matrizPesos();
    void Floyd();
};

#endif