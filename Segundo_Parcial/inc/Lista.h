#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

#ifndef LISTA_H
#define LISTA_H

struct Dato
{
    string palabra;
    int repeticiones;
};

class Nodo {
public:
    Nodo(string d){ 
        info = new Dato;
        info->palabra = d;
        info->repeticiones = 1;
    }
    ~Nodo(){
        delete info;
    }
    Dato* info;
    Nodo* der, * izq, *siguiente;
    int FB;
 
    void setNext(Nodo *next){siguiente = next;};
    Nodo* getNext() { return siguiente; };
    bool esVacio() { return siguiente == NULL;}
    void incrContador(){ info->repeticiones++;}
};


class Lista {
private: 
    Nodo* czo;
    void borrarD(string d, Nodo* ant);
public:
    Lista() { czo = nullptr; };
    void add(string d); //sumar nodos a la lista

};


void Lista::add(string d){
    Nodo* nuevo = new Nodo(d);
    nuevo->setNext(czo);
    czo = nuevo;
}

#endif 