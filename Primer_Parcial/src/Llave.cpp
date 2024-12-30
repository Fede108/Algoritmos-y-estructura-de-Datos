#include <iostream>
#include <string>
#include <fstream>
using namespace std;    

#include "../inc/Llave.h" 
#include "../inc/State.h" 
#include "../inc/Valor.h" 
#include "../inc/ExpresionJson.h" 
#include "../inc/Context.h"

bool String_ :: validarExpresion(char c){
    str += c;
    if (c == '"' && p.pilavacia()) { 
        p.apilar(c); // Abre una comilla
        return true;
    }   
    if (c == '"' && !p.pilavacia()) { 
        p.desapilar(); // Cierra una comilla
        expresionCorrecta = true;
        return true;
    }
    if (!p.pilavacia()){ // Cualquier caracter dentro de las comillas es valido
        return true;
    }
    return false;    
}

bool String_ :: getExpresionEsCorrecta(){
    return expresionCorrecta;
}

string String_ ::print(){
    return str;
}

//-------------------------------------------------------------------------------

bool Llave:: validarExpresion(char c){
    if (str->getExpresionEsCorrecta())  // Evalua expresion actual 
    {   delete str;
        str = new String_();
        if (c == ':')
        { 
            p.apilar(c); // Procesa el carácter `:`
            getContext()->setEstado(getContext()->getValor()); // Proxima expresion a evaluar  
            return true;
        }
            return false; // Error: no hay `:` después de una llave válida
    }

    if (!p.pilavacia()) {
        p.desapilar(); 
    }

    bool correcta = str->validarExpresion(c); // Continúa validando la llave actual
    if (str->getExpresionEsCorrecta())
    {
        llaves.push_back(*str);
    }
    return correcta;
}

string Llave::print(){
    if (llaves.empty()) return "";
    ostringstream resultado;
    // Accede y procesa el primer elemento
    resultado << llaves.front().print() << p.tope() << getContext()->getValor()->print();
    // Elimina el primer elemento
    llaves.erase(llaves.begin());  // Elimina el primer elemento
    return resultado.str();
}



