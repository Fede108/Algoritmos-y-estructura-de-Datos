#include <iostream>
#include <string>
using namespace std;    

#include "../inc/Expresion.h"
#include "../inc/Llave_valor.h" 

class Llave_valor : public Expresion{
    private:
       string clave;
       string valor; 
    public:
        Llave_valor(const string& linea): Expresion(linea) {}
        bool validar_linea();
        bool validar();
        bool validar_ultimaLinea();
};

bool Llave_valor :: validar(){
    clave = this->getLinea().substr(0, this->getPosSeparador());
    valor = this->getLinea().substr(this->getPosSeparador());
    if (verificarExpresion(clave,'\n','"','"') && verificarExpresion(valor,':','"','"'))
    {
        return true;
    }               
    return false;
}

bool Llave_valor :: validar_ultimaLinea(){ 
    if (validar())
    {
        return valor[valor.length() - 1] == '"' ;
    }                 
    return false;
}

bool Llave_valor :: validar_linea(){
    if (validar())
    {
        return valor[valor.length() - 1] == ',' && valor[valor.length() - 2] == '"';
    }               
    return false;
}
