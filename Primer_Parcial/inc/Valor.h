#include <string>
#include <iostream>
#include <fstream>

#include "State.h"
#include "Pila.h" 

using namespace std;    

class Context; 
class Valor;

#ifndef VALOR_H
#define VALOR_H


class EstadoInterno{
    protected:
        Valor* valor;
    public:
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
public:
    ListaString(Valor* valor);
    bool validarExpresion(char c);
};


class Valor : public State{
private:
    EstadoInterno* estadoInterno;
    String valor_string;
    ListaString lista_string;
    string expresion;
    Pila<char> p1 ;
    Pila<char> p2 ;  
protected:
    Context* ctx;

public:
    Valor(Context *contexto) : valor_string(this), lista_string(this) { ctx = contexto; estadoInterno = nullptr; }
    bool validarExpresion(char c);
    void setEstadoInterno(EstadoInterno* estado){
        estadoInterno=estado;
        if(estadoInterno == nullptr) return;
        estadoInterno->setValor(this);
    }
    EstadoInterno* getValor_string() { return &valor_string; };
    EstadoInterno* getValor_listaString() { return &lista_string; };
    Context* getContext(){return ctx;}
};




#endif 
