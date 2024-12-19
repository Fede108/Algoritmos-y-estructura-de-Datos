#include <string>
#include <iostream>
#include <fstream>

#include "State.h"
#include "Pila.h" 
#include "Context.h"
using namespace std;    


#ifndef LLAVE_H
#define LLAVE_H

class Llave : public State{
private:
    Context* ctx;
    string expresion;
    Pila<char> p;
    string valor;

public:
    void validarExpresion(char c);
    Llave(Context* contexto);
    
};

#endif 
