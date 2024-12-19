#include <string>
#include <iostream>
#include <fstream>

#include "State.h"
#include "Pila.h" 
#include "Context.h"
using namespace std;    


#ifndef LISTA_H
#define LISTA_H

class Lista : public State{
private:
    Context* ctx;
    string expresion;
    Pila<char> p ;
    string valo;

public:
    Lista(Context* contexto);
    void validarExpresion(char c);
   
};

#endif 
