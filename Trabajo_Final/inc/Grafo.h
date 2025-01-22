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
public:
    int **pesos;
    int N; 
    Vector<Router*> nodos;
    Grafo(int N, int k, int a, int t);
    ~Grafo();
    void agregarArco(int n, int m);
    void mostrarGrafo();    
    void matrizPesos();
    void Floyd();
};

#endif