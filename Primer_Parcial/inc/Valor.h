#include <string>
#include <iostream>
#include <fstream>

#include "State.h"
#include "Pila.h" 
#include "Cola.h"

using namespace std;    

class Context; 
class Valor;

#ifndef VALOR_H
#define VALOR_H


class EstadoInterno{
    protected:
        Valor* valor;
    public:
        EstadoInterno* getEstadoInterno(){ return this;};
        void setValor(Valor* valor) { this->valor = valor; }  
        virtual bool validarExpresion(char c) = 0;
};

class String:public EstadoInterno{
private:
    Pila<char> p;
public:
    String(Valor* valor);
    bool validarExpresion(char c);
};

class ListaString : public EstadoInterno{
private:
    Pila<char> p;
    Cola<char> cola;  
public:
    ListaString(Valor* valor);
    bool validarExpresion(char c);
    void agregar(char c){ cola.add(c);}
};


class Valor : public State{
private:
    EstadoInterno* estadoInterno;
    String valor_string;
    ListaString lista_string;
    string expresion;
    Pila<char> p1 ;  


public:
    Valor() : valor_string(this), lista_string(this) {  estadoInterno = nullptr; }
    bool validarExpresion(char c);
    void guardarExpresion(char c);
    string print();
    void setEstadoInterno(EstadoInterno *estado)
    {
        estadoInterno=estado;
        if(estadoInterno == nullptr) return;
        estadoInterno->setValor(this);
    }
    EstadoInterno* getValor_string() { return &valor_string; };
    EstadoInterno* getValor_listaString() { return &lista_string; };
   
};




#endif 
