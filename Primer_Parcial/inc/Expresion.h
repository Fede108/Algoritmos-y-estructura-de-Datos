#include <iostream>
#include <string>
#include <string>
#include "Pila.h"
using namespace std;

#ifndef EXPRESION_H
#define EXPRESION_H



class Expresion {
private:
    string linea;
    string buffer;
    int posicion;

public:
    Expresion(const string& linea);
    bool verificarExpresion(string cadena, char prefijo, char abierto, char cerrado);
    int getPosSeparador();
    virtual bool validar_linea() = 0;
    virtual bool validar_ultimaLinea() = 0;
    void setLinea(const string& linea);
    const string& getLinea() const;
    string guardarLinea();
};

#endif 
