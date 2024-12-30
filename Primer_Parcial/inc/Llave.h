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
};

class Llave : public State{
private:
    Pila<char> p;
    String_ *str;
    vector <String_> llaves; //buffer de strings

public:
    Llave(){
        str = new String_();
    }
    bool validarExpresion(char c);
    void guardarExpresion(char c);
    string print();
};


#endif 
