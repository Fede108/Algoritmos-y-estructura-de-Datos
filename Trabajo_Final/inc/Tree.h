#ifndef TREE_H
#define TREE_H
#include "Cola.h"
#include "Vector.h"
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

class Router;
struct Paquete;

class nodo {
public:
    nodo* der, * izq;
    Cola<Paquete*> *colaDeEspera;
    Router* router;
    int cantEnviados = 0;
    nodo (Router* router);
    ~nodo();
};

class arbol {
private:
    nodo* raiz;
    void ArbolBusq(Router* router, nodo*& nuevo);
    nodo* busca(nodo* aux, unsigned long x);
    void ird(nodo* A);
    void recorridoTransversal(nodo* n, Vector<nodo*> *r );
public:
    arbol() { raiz = NULL; }
    ~arbol() {}
    void agregarNodo(Router* router);
    nodo* buscar(int x) { return busca(raiz, x);}
    void IRD(){ird(raiz);}    // recorrido inorden del arbol  
    Vector<nodo*> listar() {
        Vector<nodo*> resultado;
        recorridoTransversal(raiz,&resultado);
        return resultado;
    };
};

#endif