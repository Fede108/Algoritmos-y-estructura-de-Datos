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
    static int i = 0;
    if (llaves.empty()) return "";
    string resultado = llaves[i].print();
    i = (i + 1) % llaves.size();
    return resultado + ":" + getContext()->getValor()->print();
}



