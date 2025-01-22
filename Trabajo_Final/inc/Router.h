#ifndef ROUTER_H
#define ROUTER_H
#include <iostream>
#include <Cola1.h>
#include <bitset>
#include "Terminal.h"
#include "Tree.h"

using namespace std;


class Router 
{
private:
    arbol vecinos;
    Vector<Lista<Paquete*>*> bufferPaginas;
//    Lista<Terminal*> *terminales;
    Lista<Paquete*> *procesarPagina;  
    Lista<Paquete*> *procesarVecinos;
    int *tablaRuta;
public:
    Vector<Terminal*> terminales;
    bitset<4> n; // nro de router
    int N; // cantidad router
    int A = 0; // ancho de banda
    int t;  // cantidad de terminales
    Terminal* terminal;
    Router(int n, int N, int A, int t) : n(n), N(N), A(A), t(t){ 
        tablaRuta = new int[N];
        procesarPagina  = new Lista<Paquete*>();
        procesarVecinos = new Lista<Paquete*>();
        for (int i = 0; i < t; i++)
        {
            terminal = new Terminal(this, i);
            terminales.push(terminal);
        }   
    };
    void agregarNodoAdyacente(Router* nodo);
    void impre();
    int tamañoCola(int n);
    void actualizarTabla(int *tabla);
    void recibirPagina(Pagina* Pagina);
    void recibirPaquete(Paquete* Paquete);
    void enviarCola(Lista<Paquete*> *paquetesPagina, Lista<Paquete*> *paquetesVecinos);
    void enviarPaquete();
    void reenvio(){ enviarPaquete();};
    void recepcion(); 
    int calcularDestino(Paquete* p);
    void almacenar(Paquete* paquete);
}; 

#endif