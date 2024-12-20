#include <string>
#include <iostream>
#include <fstream>

#include "State.h"
#include "Pila.h" 
class Context; 
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
    bool validarExpresion(char c);
    ExpresionJson(Context* contexto);
};

#endif 

