#ifndef ROUTER_H
#define ROUTER_H
#include <iostream>
#include <Cola.h>
using namespace std;

class Router;

class nodo
{
private:
    /* data */
public:
    Cola<int> *paquetes;
    Router* router;
    nodo (Router* router);
    ~nodo();
};

class Router 
{
private:
    int n; // nro de router
    Lista<nodo*> *vecinos;
    int *tablaRuta;
    void imp(Lista<nodo*>* adyacentes);
    int tamaño(Lista<nodo*>* adyacentes, int n);
public:
    Router(int n, int N) : n(n){ 
        vecinos = new Lista<nodo*>(); 
        tablaRuta = new int[N];
    };
    void agregarNodoAdyacente(Router* nodo);
    void impre(){imp(vecinos);}
    int tamañoCola(int n){return tamaño(vecinos,n);};
    void actualizarTabla(int *tabla);
};
#endif