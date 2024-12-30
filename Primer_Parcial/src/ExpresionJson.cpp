#include <iostream>
#include <string>
#include <fstream>
using namespace std;    

#include "../inc/ExpresionJson.h" 
#include "../inc/State.h" 
#include "../inc/Llave.h" 
#include "../inc/Context.h"


bool ExpresionJson:: validarExpresion(char c){  
    if(c == '\n' || c == ' ' || c == '\t' ){ return true; }
    expresion += c;
    if(c=='{')
    {
        p.apilar('{');
        getContext()->setEstado(getContext()->getLlave());
        return true;
    }   
    else if (!p.pilavacia() && c==',')
    {
       getContext()->setEstado(getContext()->getLlave());
       return true;        
    }
    else if(c=='}') 
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
    static int i = 0; 
    if (expresion.empty()) return "";
    char resultado = expresion[i++];
    if( i == expresion.size()) return "}";
    return resultado + getContext()->getLlave()->print();
}
    