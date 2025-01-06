#ifndef ARBOL_H
#define ARBOL_H


#include <cstdlib>
#include <iostream>
#include <sstream>

#include "Lista.h"

using namespace std;


class ArbolAVL
{
private:
    Nodo* raiz;
    void Insert(string x, bool &aumento, Nodo* &A);
    void Insert(string x, bool &aumento, Nodo* &A);
    void show(Nodo* aux, int n);
    void rotarLL(Nodo* &A);
    void rotarRR(Nodo* &A);
    void rotarLRalter(Nodo* &A);
    void rotarRLalter(Nodo* &A);
public:
    ArbolAVL(){raiz=NULL;};
    ~ArbolAVL(){};
    void CreaArbolAVL(string x);
    void VerArbol(){ show(raiz,0); }   
};

#endif 