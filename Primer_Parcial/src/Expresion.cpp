
#include <iostream>
#include <string>
using namespace std;    

#include "../inc/Pila.h"
#include "../inc/Expresion.h"

Expresion::Expresion(const string& linea) :  linea(linea) {}  

void Expresion:: setLinea(const string& linea) { this->linea = linea; }

const string& Expresion:: getLinea() const { return linea; }


bool Expresion:: verificarExpresion( string cadena, char prefijo, char abierto, char cerrado){
    if ( cadena[0] != prefijo || cadena[1] != abierto || cadena.length() < 4)
        return false;

    Pila<char> p;
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

