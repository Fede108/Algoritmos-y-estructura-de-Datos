#ifndef GRAFO_H
#define GRAFO_H
#include "Router.h"
#include "Vector.h"

class Grafo
{
private:
    int **matriz; //          cf --> [cf[0], cf[1], cf[2]]  (Arreglo de punteros a enteros)
    int **cf;     //        cf[0] --> [1, 2, 3]           (Primer fila de enteros)
    int **A;      //        cf[1] --> [4, 5, 6]           (Segunda fila de enteros)
                  //        cf[2] --> [7, 8, 9]           (Tercera fila de enteros) 
                                                   
public:
    int **pesos;
    int N; // cantidad de routers
    int a; // ancho de banda
    int K; // grado del grafo
    int t;
    Vector<Router*> nodos;
    Grafo(int N, int k, int a, int t);
    ~Grafo();
    void agregarArco(int n, int m);
    void mostrarGrafo();
    void mostrarCaminos();    
    void matrizPesos();
    void Floyd();
};

#endif