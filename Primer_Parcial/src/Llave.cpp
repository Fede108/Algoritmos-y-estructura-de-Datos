#include <iostream>
#include <string>
#include <fstream>
using namespace std;    

#include "../inc/Estado.h" 
#include "../inc/ExpresionJson.h"


bool Llave :: validarExpresion(char c){
    
    if (str == nullptr)
    {
        str = new String();
        bufferStrings.encolar(str);
    }
    
    if (str->getExpresionEsCorrecta())  // string ingresado es correcto 
    {   str = nullptr;
        llaves += c; // guarda el caracter
        if (c == ':')
        { 
            // llave correcta
            getExpresionJson()->setEstado(getExpresionJson()->getValor()); // siguiente modo a validar es un valor   
            return true;
        }
            return false; // error, no hay : después de un string valido
    }

    return str->validarExpresion(c); // continua validando el string actual
}

string Llave :: print(){
    ostringstream resultado;
    if (!bufferStrings.esvacia())
    {
        resultado << bufferStrings.last()->print();
        delete bufferStrings.last();                // se libera la memoria del puntero al objeto String
        bufferStrings.borrar_last();                // elimina el primer elemento
    } 
    if (!llaves.empty())
    {
        resultado << llaves.front();
        llaves.erase(llaves.begin());
    }         
    resultado << getExpresionJson()->getValor()->print();
    return resultado.str();
}



