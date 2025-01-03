#include <iostream>
#include <string>
#include <fstream>
using namespace std;    

#include "../inc/Estado.h" 
#include "../inc/ExpresionJson.h"


bool EntreLlaves :: validarExpresion(char c){  
    expresion += c;
    if(c=='{')
    {
        p.apilar('{');
        getExpresionJson()->setEstado(getExpresionJson()->getLlave());
        return true;
    }   
    if (!p.pilavacia() && c==',')
    {
       getExpresionJson()->setEstado(getExpresionJson()->getLlave());
       return true;        
    }
    if(c=='}') 
    {
       p.desapilar();
       return true;
    }
    return false;        
}
 
int EntreLlaves :: size(){
    return  expresion.size();
}

string EntreLlaves :: print(){
    ostringstream resultado;
    if(expresion.empty()) return "";
    if(expresion.front() == '}' )
    {
        resultado << expresion.front(); 
    }else{
        resultado << expresion.front() << getExpresionJson()->getLlave()->print();
    }
    expresion.erase(expresion.begin());
    return resultado.str();
}
    