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
     Expresion() {
         // Inicialización por defecto
    }
    bool verificarExpresion(string cadena, char prefijo, char abierto, char cerrado);
    int getPosSeparador();
    void setLinea(const string& linea);
    const string& getLinea() const;
    string guardarLinea();
    
};

#endif 
