#include <string>
#include <iostream>
#include <fstream>
#include <vector>


#include "State.h"
#include "Pila.h" 
#include "Cola.h"
#include "Llave.h"

using namespace std;    

class Context; 
class Valor;

#ifndef VALOR_H
#define VALOR_H


class ListaString: public Dato
{
private:
    bool expresionCorrecta = false;
    Pila<char> p;
    Cola<char> cola;
    vector <String_> strings; //BUFFER
    String_ *str;  
    string cadena;
public:
    ListaString();
    bool getExpresionEsCorrecta();
    bool validarExpresion(char c);
    void agregar(char c){ cola.add(c);}
    string print();
    bool pilaEmpty( ){return p.pilavacia();};
};


class Valor : public State{
private:
    Dato *valorDato;
    vector <Dato*> valores; //BUFFER
    Pila<char> p1;  
public:
    Valor()  { valorDato = nullptr;}
    bool validarExpresion(char c);
    bool validarValor(){ 
        if (valorDato == nullptr) return true;
        return valorDato->pilaEmpty();};
    string print();
};

#endif 
