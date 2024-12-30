#include <iostream>
#include <string>
#include <fstream>
using namespace std;    

#include "../inc/ExpresionJson.h" 
#include "../inc/State.h" 
#include "../inc/Llave.h" 
#include "../inc/Context.h"


bool ExpresionJson:: validarExpresion(char c){  
    expresion += c;
    if(c=='{')
    {
        p.apilar('{');
        getContext()->setEstado(getContext()->getLlave());
        return true;
    }   
    if (!p.pilavacia() && c==',')
    {
       getContext()->setEstado(getContext()->getLlave());
       return true;        
    }
    if(c=='}') 
    {
       p.desapilar();
       return true;
    }
    return false;        
}
 

int ExpresionJson ::size(){
    return expresion.length();
}

string ExpresionJson :: print(){
    ostringstream resultado;
    if (expresion.empty()) return "";
    resultado << expresion.front() << getContext()->getLlave()->print();
    expresion.erase(expresion.begin());
    return resultado.str();
}
    