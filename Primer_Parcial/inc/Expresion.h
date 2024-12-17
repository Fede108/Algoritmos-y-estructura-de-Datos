
#include <iostream>
#include "Pila.h"
using namespace std;    

#ifndef EXPRESION_H
#define EXPRESION_H
class Expresion
{
private:
    string linea;
    Pila<char> p;
    string buffer;
    int posicion;
public:  
    Expresion(string linea) :  linea(linea) {};
    bool verificarExpresion( string cadena, char prefijo, char abierto, char cerrado);
    int getPosSeparador();
    virtual bool validar() = 0;
    virtual bool validar_ultimaLinea() = 0;
    void setLinea(const string& linea) { this->linea = linea; }
    const string& getLinea() const { return linea; }
    string guardarLinea();
};



bool Expresion:: verificarExpresion( string cadena, char prefijo, char abierto, char cerrado){
    if ( cadena[0] != prefijo || cadena[1] != abierto || cadena.length() < 4)
        return false;

    p.apilar(cadena[1]);
    int indice = 2;
            while ( indice<cadena.length() && ! p.pilavacia() )
            {
                if(cadena[indice] == cerrado){
                   p.desapilar();
                }
                indice++;   
            }
    return p.pilavacia();    
}


int Expresion:: getPosSeparador(){
    for (int i = 0; i < linea.length(); i++) {
        if (linea[i] == ':') {
           return i;
        }
    }
    return 0;
}

string Expresion :: guardarLinea(){
    for (int i = 0; i < linea.length(); i++)
    {
        if (linea[i] == '\n' || linea[i] == ' ' || linea[i] == '\t' ){}
        else{
            buffer += linea[i]; 
        }   
    }
    return buffer;
}

#endif