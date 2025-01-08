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

class NodoAbb {
public:
    Dato* info;
    NodoAbb* der, * izq, *siguiente;
    int FB;
 
    NodoAbb(string d){ 
        info = new Dato;
        info->palabra = d;
        info->repeticiones = 1;
    }
    ~NodoAbb(){
        delete info;
    }
 
    void setNext(NodoAbb *next){siguiente = next;};
    void incrContador(){ info->repeticiones++;}
};

class ArbolAVL
{
private:
    NodoAbb* raiz;
    NodoAbb* czo;
    void Insert(string x, bool &aumento, NodoAbb* &A);
    void show(NodoAbb* aux, int n);
    void rotarLL(NodoAbb* &A);
    void rotarRR(NodoAbb* &A);
    void rotarLRalter(NodoAbb* &A);
    void rotarRLalter(NodoAbb* &A);
    void ird(NodoAbb* A);
    void impre(NodoAbb* A);
    ArbolAVL* copy(NodoAbb* A,ArbolAVL* &Arbol);
public:
    ArbolAVL(){raiz=NULL; czo = NULL;};
    ~ArbolAVL(){};
    void CreaArbolAVL(string x);
    void VerArbol(){ show(raiz,0); } 
    void IRD(){ird(raiz);}; // recorrido inorden del arbol  
    void print(){impre(czo);}; // imprime la lista
    ArbolAVL* Copy(void){   ArbolAVL* arbol = new ArbolAVL(); // devuelve copia de la lista en inorden 
        return copy(raiz, arbol);}; 
    NodoAbb* last(); // devuelve el primer NodoAbb de la lista
    ArbolAVL* resto(); //retorna el puntero al "resto" de la lista
};

#endif 