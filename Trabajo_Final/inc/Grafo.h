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
    vectorClass<Router*> nodos;
    Grafo(int N, int K, int a);
    ~Grafo();
    void agregarArco(int n, int m);
    void mostrarGrafo();    
    void matrizPesos();
    void Floyd();
};

#endif