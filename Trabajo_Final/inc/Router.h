#ifndef ROUTER_H
#define ROUTER_H
#include <iostream>
#include <Cola.h>
#include "Terminal.h"
#include "Tree.h"

using namespace std;


class Router 
{
private:
    
    arbol *vecinos;
//    Lista<Terminal*> *terminales;
    Lista<Paquete*> *paquetesEnviar;
    int *tablaRuta;
//Paquete* paquete;
    void imp();
    int tamaño( int n);
public:
    int n; // nro de router
    int N; // cantidad router
    Terminal* terminal;
    Router(int n, int N) : n(n), N(N){ 
        vecinos = new arbol(); 
        tablaRuta = new int[N];
        paquetesEnviar = new Lista<Paquete*>();
    };
    void agregarNodoAdyacente(Router* nodo);
    void impre(){imp();}
    int tamañoCola(int n){return tamaño(n);};
    void actualizarTabla(int *tabla);
    void recibirPagina(Pagina Pagina);
    void recibirPaquete(Paquete Paquete);
    void enviarCola();
    void enviarPaquete();
};
#endif