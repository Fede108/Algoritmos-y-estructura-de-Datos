#ifndef ROUTER_H
#define ROUTER_H
#include <iostream>
#include <Cola.h>
#include "../inc/Terminal.h"
using namespace std;

class Router;

class nodo
{
private:
    /* data */
public:
    Cola<Paquete> *paquetes;
    Router* router;
    nodo (Router* router);
    ~nodo();
};

class Router 
{
private:
    int n; // nro de router
    Lista<nodo*> *vecinos;
    Lista<Paquete> *paquetesEnviar;
    int *tablaRuta;
    Terminal* terminal;
    Paquete* paquete;
    void imp(Lista<nodo*>* adyacentes);
    int tamaño(Lista<nodo*>* adyacentes, int n);
public:
    Router(int n, int N) : n(n){ 
        vecinos = new Lista<nodo*>(); 
        tablaRuta = new int[N];
        paquetesEnviar = new Lista<Paquete>();
    };
    void agregarNodoAdyacente(Router* nodo);
    void impre(){imp(vecinos);}
    int tamañoCola(int n){return tamaño(vecinos,n);};
    void actualizarTabla(int *tabla);
    void recibirPagina(Pagina Pagina);
    void recibirPaquete(Paquete Paquete);
    void enviarCola(Lista<nodo*>* adyacentes, int destino);
    void enviarPaquete(Lista<nodo*>* adyacentes);
};
#endif