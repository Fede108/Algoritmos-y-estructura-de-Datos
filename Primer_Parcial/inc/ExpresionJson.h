#include <string>
#include <iostream>
#include <fstream>

#include "State.h"
#include "Pila.h" 
#include "Llave.h"

class Context; 
using namespace std;    

#ifndef EXPRESIONJSON_H
#define EXPRESIONJSON_H

class ExpresionJson : public State, public Dato {
private:
    string expresion;
    Pila<char> p;

public:
    // Métodos de ExpresionJson
    bool validarExpresion(char c) override;
    void guardarExpresion(char c);
    string print() override;
    int size();
    bool validarJson() { return p.pilavacia(); }

    // Implementaciones de los métodos virtuales de Dato
    bool getExpresionEsCorrecta() override { return validarJson(); }
    bool pilaEmpty() override { return p.pilavacia(); }
};

#endif 

