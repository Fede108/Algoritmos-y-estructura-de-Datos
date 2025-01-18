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
    int *tablaVecinos;
    Paquete* paquete;
    void imp();
    int tamaño( int n);
public:
    int n; // nro de router
    int N; // cantidad router
    int K = 0; // cantidad de vecinos
    int i = 0; 
    Terminal* terminal;
    Router(int n, int N, int K) : n(n), N(N), K(K){ 
        vecinos = new arbol(); 
        tablaRuta = new int[N];
        tablaVecinos = new int[K];
        paquetesEnviar = new Lista<Paquete*>();
        paquete = NULL;
    };
    void agregarNodoAdyacente(Router* nodo);
    void impre(){imp();}
    int tamañoCola(int n){return tamaño(n);};
    void actualizarTabla(int *tabla);
    void recibirPagina(Pagina Pagina);
    void recibirPaquete(Paquete* Paquete);
    void enviarCola();
    void enviarPaquete();
    void enviarVecino();
    void reenviar(); 
};
#endif