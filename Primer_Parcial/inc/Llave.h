#include <string>
#include <iostream>
#include <fstream>

#include "State.h"
#include "Pila.h" 
using namespace std;    
class Context; 

#ifndef LLAVE_H
#define LLAVE_H

class Llave : public State{
private:
    Context* ctx;
    string expresion;
    Pila<char> p;
    string valor;

public:
    bool validarExpresion(char c);
    Llave(Context* contexto);
    
};

#endif 
