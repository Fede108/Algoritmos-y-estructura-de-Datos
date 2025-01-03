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
        strings.encolar(str);
    }
    
    if (str->getExpresionEsCorrecta())  // Evalua expresion actual 
    {   str = nullptr;
        llaves += c; // Guarda el caracter
        if (c == ':')
        { 
            getExpresionJson()->setEstado(getExpresionJson()->getValor()); // Proxima expresion a evaluar  
            return true;
        }
            return false; // Error: no hay `:` después de una llave válida
    }

    return str->validarExpresion(c); // Continúa validando el string actual;
}

string Llave :: print(){
    if (strings.esvacia()) return "";
    ostringstream resultado;
    if(llaves.empty()){
        resultado << strings.last()->print() << getExpresionJson()->getValor()->print(); 
    } else{
       resultado << strings.last()->print() << llaves.front() << getExpresionJson()->getValor()->print();
       llaves.erase(llaves.begin());
    }
    strings.borrar_last(); // Elimina el primer elemento
    return resultado.str();
}



