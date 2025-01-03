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
        strings.push_back(str);
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
    if (strings.empty()) return "";
    ostringstream resultado;
    if(llaves.empty()){
        resultado << strings.front()->print() << getExpresionJson()->getValor()->print(); 
    } else{
       resultado << strings.front()->print() << llaves.front() << getExpresionJson()->getValor()->print();
       llaves.erase(llaves.begin());
    }
    delete strings.front(); // Elimina el primer elemento
    strings.erase(strings.begin());  
   
    return resultado.str();
}



