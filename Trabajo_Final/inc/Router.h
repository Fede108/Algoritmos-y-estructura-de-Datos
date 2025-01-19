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
    Lista<Paquete*> *procesarPagina;  
    Lista<Paquete*> *procesarVecinos;
    int *tablaRuta;
public:
    int n; // nro de router
    int N; // cantidad router
    int K = 0; // cantidad de vecinos
    int A = 0; // ancho de banda
    Terminal* terminal;
    Router(int n, int N, int K, int A) : n(n), N(N), K(K), A(A){ 
        vecinos = new arbol(); 
        tablaRuta = new int[N];
        procesarPagina  = new Lista<Paquete*>();
        procesarVecinos = new Lista<Paquete*>();
        terminal = new Terminal(this);
    };
    
    void agregarNodoAdyacente(Router* nodo);
    void impre();
    int tamañoCola(int n);
    void actualizarTabla(int *tabla);
    void recibirPagina(Pagina Pagina);
    void recibirPaquete(Paquete* Paquete);
    void enviarCola(Lista<Paquete*> *paquetesPagina, Lista<Paquete*> *paquetesVecinos);
    void enviarPaquete();
    void reenvio(){ enviarPaquete();};
    void recepcion(); 
    int calcularDestino(Paquete* p);
}; 

#endif