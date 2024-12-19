#include <string>
#include <iostream>
#include <fstream>

#include "State.h"
#include "Pila.h" 
#include "Context.h"
using namespace std;    

#ifndef EXPRESIONJSON_H
#define EXPRESIONJSON_H
class ExpresionJson : public State
{
private:
    Context* ctx;
    string expresion;
    Pila<char> p ;
   
public:
    void validarExpresion(char c);
    ExpresionJson(Context* contexto);
};

#endif 

