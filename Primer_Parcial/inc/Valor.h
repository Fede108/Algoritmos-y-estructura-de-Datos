#include <string>
#include <iostream>
#include <fstream>

#include "State.h"
#include "Pila.h" 

using namespace std;    

class Context; 
#ifndef VALOR_H
#define VALOR_H

class Valor : public State{
private:
    Context* ctx;
    string expresion;
    Pila<char> p1 ;
    Pila<char> p2 ;    
    string valo;

public:
    Valor(Context* contexto);
    bool validarExpresion(char c);
};

#endif 
