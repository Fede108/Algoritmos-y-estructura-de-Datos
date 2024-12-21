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
    string expresion;
    Pila<char> p;
    string valor;

public:
    bool validarExpresion(char c);
    void guardarExpresion(char c);
    string print();
   
};

#endif 
