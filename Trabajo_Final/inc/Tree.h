#ifndef TREE_H
#define TREE_H
#include "Cola1.h"
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
    int paqPagRecibidas = 0;
    int anchoBanda;
    int colaSize = 0;
    int ciclos = 1;
    nodo (Router* router, int anchoBanda);
    ~nodo();
    Paquete* getTope();  // devuelve el tope de la colaDeEspera y la desencola
    void encolar(Paquete* p);
};

class arbol {
private:
    nodo* raiz;
    void ArbolBusq(Router* router, nodo*& nuevo, int anchoBanda);
    nodo* busca(nodo* aux, int ip);
    void ird(nodo* A);
    void recorridoTransversal(nodo* n, Vector<nodo*> *r );
public:
    arbol() { raiz = NULL; }
    ~arbol() {}
    void agregarNodo(Router* router, int anchoBanda);
    nodo* buscar(int ip) { return busca(raiz, ip);}
    void IRD(){ird(raiz);}      
    Vector<nodo*> listar() {
        Vector<nodo*> resultado;
        recorridoTransversal(raiz,&resultado);
        return resultado;
    };
};

#endif