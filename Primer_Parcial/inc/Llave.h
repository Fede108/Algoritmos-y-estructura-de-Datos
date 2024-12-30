#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "State.h"
#include "Pila.h" 
using namespace std;    
class Context; 

#ifndef LLAVE_H
#define LLAVE_H

class Dato
{
public:
    virtual bool validarExpresion(char c)= 0;
    virtual bool  getExpresionEsCorrecta() = 0;
    virtual string print() = 0;
    virtual bool pilaEmpty() = 0;
};


class String_ : public Dato
{
private:
    Pila<char> p;
    bool expresionCorrecta = false;
    string str; //buffer de char
public:
    bool validarExpresion(char c);
    bool getExpresionEsCorrecta();
    string print();
    bool pilaEmpty(){return p.pilavacia();};
};

class Llave : public State{
private:
    String_ *str;
    vector <String_> llaves; //buffer de strings
    Pila<char> p;
public:
    Llave(){
        str = new String_();
    }
    ~Llave() {
        delete str;
    }
    bool validarExpresion(char c);
    string print();
    bool validarLlave( ){ 
        return !p.pilavacia() && str->pilaEmpty();
    };
};


#endif 
