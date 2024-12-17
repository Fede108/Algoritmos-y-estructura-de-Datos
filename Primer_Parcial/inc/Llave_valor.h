#include <string>
#include <iostream>
#include "Expresion.h"
using namespace std;    


#ifndef LLAVE_VALOR_H
#define LLAVE_VALOR_H



class Llave_valor : public Expresion {
private:
    string clave;
    string valor;

public:
    Llave_valor(const string& linea);
    bool validar_linea();
    bool validar();
    bool validar_ultimaLinea();
};

#endif 
