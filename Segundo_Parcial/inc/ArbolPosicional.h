#ifndef ARBOL_POSICIONAL_H
#define ARBOL_POSICIONAL_H

#include <string>
#include <fstream>

#include "ListaConAbb.h"
#include "Pila.h"

using namespace std;

class Nodo 
{
public:
   NodoAbbLista* hoja;   // hoja es un puntero a los nodos de la lista
   Nodo* der;
   Nodo* izq;
   int altura;
   Nodo(){
    hoja    = NULL;
    der     = NULL;
    izq     = NULL;
    altura  = 0;
   }
};

class ArbolPosicional
{
private:
    Nodo* raiz;
    Pila<int> pila;
    void ArbolPos(ListaConAbb *&T, Nodo*& nuevo, int altura); // modifica el puntero lista (que es copia del original) usando *&T  
    void imprimir(Nodo* NodoAbbLista);           // imprime las hojas del arbol
    int calcularAltura(int numElementos);   // calcula altura del arbol segun nro elementos de la lista
    void show(Nodo* aux, int n);            // imprime el arbol 
public:
    ArbolPosicional(){
          raiz = NULL;
    };
    void CreaArbolPos(ListaConAbb *lista) // recibe una copia del puntero a la lista, no puede modificar direccion del original
    {  
        ArbolPos(lista,raiz,calcularAltura(lista->cabeza()->n));     // crea arbolPos en una llamada segun cantidad nodos de lista
    };
    void ImprimirHojas(){imprimir(raiz);};
    void swap(int p1, int p2);    
    NodoAbbLista* recorrer(int bin, Nodo* Nodo);
    Dato* posicion(int p);
    void verArbol(){ show(raiz,0);}
    void convertirBin(int n);
};

#endif