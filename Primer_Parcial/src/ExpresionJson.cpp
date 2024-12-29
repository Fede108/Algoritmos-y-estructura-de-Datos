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

void ExpresionJson ::guardarExpresion(char c){
    if(c == '\n' || c == ' ' || c == '\t' ){ return ; }
     expresion += c;
}

string ExpresionJson ::print(){
    return expresion;
}
    