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
    if (c == '"' && p.pilavacia()){ 
        p.apilar(c);
        return true;
    }   
    if (c == '"' && !p.pilavacia()){ 
        p.desapilar();
        expresionCorrecta = true;
        return true;
    }
    else if (!p.pilavacia()){
        return true;
    }
    return false;    
}

bool String_ :: getExpresionEsCorrecta(){
    return expresionCorrecta;
}

void String_ :: reiniciarExpresion(){
    expresionCorrecta = false;
}

string String_ ::print(){
    return str;
}

bool Llave:: validarExpresion(char c){
    if (c == '\n' || c == ' ' || c == '\t' ) return true;
    if (str->getExpresionEsCorrecta())
    {   
        llaves.push_back(*str);
        delete str;
        str = new String_();
        if (c == ':')
        {
            getContext()->setEstado(getContext()->getValor());
            return true;
        }
        else
        {
            return false;
        }
    }
    return str->validarExpresion(c);
}

string Llave::print(){
    return llaves.at(0).print();
}

void Llave::guardarExpresion(char c){
    if(c == '\n' || c == ' ' || c == '\t' ){ return ; }
    expresion += c;
}

