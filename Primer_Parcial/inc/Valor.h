#include <string>
#include <iostream>
#include <fstream>

#include "Expresion.h"
using namespace std;    


#ifndef LLAVE_VALOR_H
#define LLAVE_VALOR_H

#include <string>
#include <iostream>
#include "Expresion.h"

class Valor{
private:
    string expresion;
    Pila<char> p ;
    string valor;

public:
    Valor() {
         // Inicialización por defecto
    }
    bool validar_linea();
    bool validar();
    bool validar_ultimaLinea();
    bool pilavacia();
    void guardar(string comando);
    void desapilar();
    void apilar(char c);
    bool evaluar_llave(char c );
};

#endif 
