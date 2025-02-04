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

class NodoAbb {   // nodo de lista y nodo de arbol
public:
    Dato* info;
    NodoAbb* der, * izq, *siguiente;
    int FB;  // fb = izq - der
    int n; // nro de nodo
    NodoAbb(string d){ 
        info = new Dato;
        info->palabra = d;
        info->repeticiones = 1;
        siguiente = NULL;
        n = -1;  // empiezo a enumerar desde el cero
    }
    ~NodoAbb(){
        delete info;
    }
 
    void setNext(NodoAbb *next){siguiente = next;};
    void incrContador(){ info->repeticiones++;}
};

// estructura combinada de lista con arbol
class ArbolAVL
{
private:
    NodoAbb* raiz;
    NodoAbb* czo;
    void Insert(string x, bool &aumento, NodoAbb* &A);
    void rotarLL(NodoAbb* &A);
    void rotarRR(NodoAbb* &A);
    void rotarLRalter(NodoAbb* &A);
    void rotarRLalter(NodoAbb* &A);
    void ird(NodoAbb* A);
    void impre(NodoAbb* A);
    ArbolAVL* copy(NodoAbb* A,ArbolAVL* &Arbol);
    void show(NodoAbb* aux, int n);
public:
    ArbolAVL(){raiz=NULL; czo = new NodoAbb("");};
    ~ArbolAVL(){};
    void CreaArbolAVL(string x);
    void IRD(){ird(raiz);};     // recorrido inorden del arbol  
    void print(){impre(czo);};  // imprime la lista
    ArbolAVL* Copy(void){  
        ArbolAVL* arbol = new ArbolAVL(); // devuelve copia del arbol 
        return copy(czo, arbol);}; 
    NodoAbb* cabeza();    // devuelve el primer nodo de la lista
    ArbolAVL* resto();    // retorna el puntero al "resto" de la lista
    void VerArbol(){ show(raiz,0); } 
};

#endif 