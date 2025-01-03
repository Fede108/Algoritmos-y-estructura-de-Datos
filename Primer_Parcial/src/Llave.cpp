#include <iostream>
#include <string>
#include <fstream>
using namespace std;    

#include "../inc/Estado.h" 
#include "../inc/ExpresionJson.h"


bool Llave :: validarExpresion(char c){
    if (str->getExpresionEsCorrecta())  // Evalua expresion actual 
    {   delete str;
        str = new String();
        llaves += c; // Guarda el caracter
        if (c == ':')
        { 
            p.apilar(c); // Procesa el carácter `:`
            getExpresionJson()->setEstado(getExpresionJson()->getValor()); // Proxima expresion a evaluar  
            return true;
        }
            return false; // Error: no hay `:` después de una llave válida
    }

    if (!p.pilavacia()) {
        p.desapilar(); 
    }

    bool correcta = str->validarExpresion(c); // Continúa validando el string actual
    if (str->getExpresionEsCorrecta())
    {
        strings.push_back(*str);
    }
    return correcta;
}

string Llave :: print(){
    if (strings.empty()) return "";
    ostringstream resultado;
    // Accede y procesa el primer elemento
    resultado << strings.front().print() << llaves.front() << getExpresionJson()->getValor()->print();
    // Elimina el primer elemento
    strings.erase(strings.begin());  // Elimina el primer elemento
    llaves.erase(llaves.begin());
    return resultado.str();
}



