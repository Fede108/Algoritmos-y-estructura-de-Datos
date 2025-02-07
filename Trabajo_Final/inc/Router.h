#ifndef ROUTER_H
#define ROUTER_H
#include <iostream>
#include "Cola.h"
#include <bitset>
#include "Terminal.h"
#include "Tree.h"
#include "Hash.h"
using namespace std;

class Router 
{
private:
    arbol vecinos;   // arbol binario con punteros a los router vecinos
    Hash<Lista<Paquete>*>  bufferPaginas; // estructura para almacenar las paginas de las terminales
    Lista<Paquete*> procesarPagina;    
    Lista<Paquete*> procesarVecinos;                               
    Hash<nodo*> vecinosEncolados;   
    int *tablaRuta;
public:
    Hash<Terminal*> terminales;   // terminales conectadas al router
    int ip;  // nro de router
    int t;   // cantidad de terminales
    
    Router(int n, int t, int* &tabla) : ip(n), t(t){ 
        tablaRuta = tabla;
        for (int i = 0; i < t; i++)
        {
            terminales.add(i, new Terminal(this, i));
        }   
    };

    ~Router() {
        delete[] tablaRuta; 
    }

    void agregarNodoAdyacente(Router* nodo, int anchoBanda);
    void impre();
    int  tamañoCola(int n);
    int  ciclos(int n);
    void recibirPagina(Pagina* Pagina);
    void recibirPaquete(Paquete* Paquete);
    void enviarColaEspera(Lista<Paquete*> *paquetesPagina, Lista<Paquete*> *paquetesVecinos);
    bool procesarPaquete(Paquete* p, bool pagCliente);
    void reenvio();
    void procesamiento(); 
    int  calcularDestino(int destino);
    void almacenar(Paquete* paquete);
    int  ruta(int destino);
    void imprimirRuta(Paquete* p);

}; 

#endif