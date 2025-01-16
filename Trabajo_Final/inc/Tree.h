#ifndef TREE_H
#define TREE_H
#include "Cola.h"

#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

class Router;
struct Paquete;

class nodo {
public:
    nodo* der, * izq;
    Cola<Paquete*> *paquetes;
    Router* router;
    nodo (Router* router);
    ~nodo();
};

class arbol {
private:
    nodo* raiz;
    void ArbolBusq(Router* router, nodo*& nuevo);
    nodo* buscar(nodo* aux, int x);
    void ird(nodo* A);
public:
    arbol() { raiz = NULL; }
    ~arbol() {}
    void CreaArbolBus(Router* router);
    nodo* busca(int x) { return buscar(raiz, x);}
    void IRD(){ird(raiz);}    // recorrido inorden del arbol  
};


#endif