#include <iostream>
#include <string>
using namespace std;    

#include "../inc/Expresion.h"
#include "../inc/Llave_valor.h" 

Llave_valor :: Llave_valor(const string& linea): Expresion(linea) {}

bool Llave_valor :: validar(){

    clave = this->getLinea().substr(0, this->getPosSeparador() + 1 );
    valor = this->getLinea().substr(this->getPosSeparador() + 1);
    if (verificarExpresion(clave,':','"','"') && verificarExpresion(valor,',','"','"'))
    {
        return true;
    }               
    return false;
}

bool Llave_valor :: validar_ultimaLinea(){ 
    if (validar())
    {
        return true;
       // return valor[valor.length() - 1] == '"' ;
    }                 
    return false;
}

bool Llave_valor :: validar_linea(){
    if (validar())
    {
        return true;
        //return valor[valor.length() - 1] == ',' && valor[valor.length() - 2] == '"';
    }               
    return false;
}
