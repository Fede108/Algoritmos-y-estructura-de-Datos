#include <iostream>
#include <string>
#include <fstream>
using namespace std;    

#include "../inc/Estado.h" 
#include "../inc/ExpresionJson.h"


bool EntreLlaves :: validarExpresion(char c){  
    expresion += c; // se guarda buffer caracteres correctos e incorrectos
    if(c=='{')    // empieza una nueva expresion
    {
        p.apilar('{');  
        getExpresionJson()->setEstado(getExpresionJson()->getLlave());  // siguiente modo a validar es una llave
        return true;
    } 
    if (!p.pilavacia() && c==',') // sigue con expresion actual
    {
       getExpresionJson()->setEstado(getExpresionJson()->getLlave()); // siguiente modo a validar es una llave
       return true;        
    }
    if(!p.pilavacia() && c=='}') // termina expresion actual
    {
       p.desapilar();
       return true;
    }
    return false;  // error en el caracter ingresado      
}
 
int EntreLlaves :: size(){
    return  expresion.size();
}

string EntreLlaves :: print(){
    ostringstream resultado;
    while(expresion.front() == '}' )
    {
        resultado << expresion.front();
        expresion.erase(expresion.begin());
    }
    if(!expresion.empty())
    {
        resultado << expresion.front();
        expresion.erase(expresion.begin());  
    } 
    resultado << getExpresionJson()->getLlave()->print(); // retorna el caracter seguido resto de expresion
    return resultado.str();
}
    