#ifndef LISTA_CON_ABB_H
#define LISTA_CON_ABB_H

#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

struct Dato
{
    string palabra;
    int repeticiones;
};

class NodoAbbLista {   // nodo de lista y nodo de arbol
public:
    Dato* info;
    NodoAbbLista* der, * izq, *siguiente;
    int FB;  // fb = izq - der
    int n; // nro de nodo
    NodoAbbLista(string d){ 
        info = new Dato;
        info->palabra = d;
        info->repeticiones = 1;
        siguiente = NULL;
        n = -1;  // empiezo a enumerar desde el cero
    }
     NodoAbbLista(string d, int repeticiones, int n){ 
        info = new Dato;
        info->palabra = d;
        info->repeticiones = repeticiones;
        this->n = n;
    } 
    ~NodoAbbLista(){
        delete info;
    }
 
    void setNext(NodoAbbLista* next){siguiente = next;};
    void incrContador(){ info->repeticiones++;}
};

// estructura combinada de lista con arbol
class ListaConAbb
{
private:
    NodoAbbLista* raiz;
    NodoAbbLista* czo;
    void Insert(string x, bool &aumento, NodoAbbLista* &A);
    void rotarLL(NodoAbbLista* &A);
    void rotarRR(NodoAbbLista* &A);
    void rotarLRalter(NodoAbbLista* &A);
    void rotarRLalter(NodoAbbLista* &A);
    void ird(NodoAbbLista* A);
    void impre(NodoAbbLista* A);
    ListaConAbb* copy(NodoAbbLista* A,ListaConAbb* &Arbol);
    void show(NodoAbbLista* aux, int n);
public:
    ListaConAbb(){raiz=NULL; czo = new NodoAbbLista("");};
    ~ListaConAbb(){};
    void CreaListaConAbb(string x);
    void IRD(){ird(raiz);};     // recorrido inorden del arbol  
    void print(){impre(czo);};  // imprime la lista
    ListaConAbb* Copy(void){  
        ListaConAbb* arbol = new ListaConAbb(); // devuelve copia del arbol 
        return copy(raiz, arbol);}; 
    NodoAbbLista* cabeza();    // devuelve el primer nodo de la lista
    ListaConAbb* resto();    // retorna el puntero al "resto" de la lista
    void VerArbol(){ show(raiz,0); } 
};

#endif 