#ifndef ROUTER_H
#define ROUTER_H
#include <iostream>
#include <Cola1.h>
#include <bitset>
#include "Terminal.h"
#include "Tree.h"
#include "Hash.h"
using namespace std;


class Router 
{
private:
    arbol vecinos;   // arbol binario con punteros a los router vecinos
    Hash<Lista<Paquete*>*>  bufferPaginas; // estructura para almacenar las paginas de las terminales
    Lista<Paquete*> *procesarPagina;    
    Lista<Paquete*> *procesarVecinos;  
    int *tablaRuta;
public:
    Hash<Terminal*> terminales;   // terminales conectadas al router
    bitset<8> ip; // nro de router
    int N; // cantidad router
    int A = 0; // ancho de banda
    int t;  // cantidad de terminales
    Terminal* terminal;
    Router(int n, int N, int A, int t) : ip(n), N(N), A(A), t(t){ 
        tablaRuta = new int[N];
        procesarPagina  = new Lista<Paquete*>();
        procesarVecinos = new Lista<Paquete*>();
        for (int i = 0; i < t; i++)
        {
            terminal = new Terminal(this, i);
            terminales.add(terminal->ip.to_ulong(),terminal);
        }   
    };
    ~Router() {
        delete[] tablaRuta; 
        delete procesarPagina; 
        delete procesarVecinos;
    }
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
    int calcularDestino(int destino);
    void almacenar(Paquete* paquete);
}; 

#endif