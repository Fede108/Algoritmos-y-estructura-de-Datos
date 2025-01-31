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
    int **caminos;   // para poder imprimir la ruta completa
public:
    Hash<Terminal*> terminales;   // terminales conectadas al router
    bitset<8> ip; // nro de router
    int t;        // cantidad de terminales
    
    Router(int n, int t, int* &tabla ,int** &caminos) : ip(n), t(t), caminos(caminos){ 
        tablaRuta = tabla;
        procesarPagina  = new Lista<Paquete*>();
        procesarVecinos = new Lista<Paquete*>();
        for (int i = 0; i < t; i++)
        {
            terminales.add(i, new Terminal(this, i));
        }   
    };

    ~Router() {
        delete[] tablaRuta; 
        delete procesarPagina; 
        delete procesarVecinos;
    }

    void agregarNodoAdyacente(Router* nodo, int anchoBanda);
    void impre();
    int tamañoCola(int n);
    int anchoBanda(int n);
    void recibirPagina(Pagina* Pagina);
    void recibirPaquete(Paquete* Paquete);
    void enviarColaEspera(Lista<Paquete*> *paquetesPagina, Lista<Paquete*> *paquetesVecinos);
    void reenvio();
    void procesamiento(); 
    int calcularDestino(int destino);
    void almacenar(Paquete* paquete);
    void ruta(int destino, int origen);
    void imprimirRuta(Paquete* p);
}; 

#endif