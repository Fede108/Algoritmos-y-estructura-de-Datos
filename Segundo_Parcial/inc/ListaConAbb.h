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

class Nodo {
public:
    Dato* info;
    Nodo* der, * izq, *siguiente;
    int FB;
 
    Nodo(string d){ 
        info = new Dato;
        info->palabra = d;
        info->repeticiones = 1;
    }
    ~Nodo(){
        delete info;
    }
 
    void setNext(Nodo *next){siguiente = next;};
    void incrContador(){ info->repeticiones++;}
};

class ArbolAVL
{
private:
    Nodo* raiz;
    Nodo* czo;
    void Insert(string x, bool &aumento, Nodo* &A);
    void show(Nodo* aux, int n);
    void rotarLL(Nodo* &A);
    void rotarRR(Nodo* &A);
    void rotarLRalter(Nodo* &A);
    void rotarRLalter(Nodo* &A);
    void ird(Nodo* A);
    void impre(Nodo* A);
    ArbolAVL* copy(Nodo* A,ArbolAVL* &Arbol);
public:
    ArbolAVL(){raiz=NULL; czo = NULL;};
    ~ArbolAVL(){};
    void CreaArbolAVL(string x);
    void VerArbol(){ show(raiz,0); } 
    void IRD(){ird(raiz);}; // recorrido inorden del arbol  
    void print(){impre(czo);}; // imprime la lista
    ArbolAVL* Copy(void){   ArbolAVL* arbol = new ArbolAVL(); 
        return copy(raiz, arbol);};
};

#endif 