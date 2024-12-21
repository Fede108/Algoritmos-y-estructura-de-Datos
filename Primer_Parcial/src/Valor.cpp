#include <iostream>
#include <string>
#include <fstream>
using namespace std;    

#include "../inc/Valor.h" 
#include "../inc/State.h" 
#include "../inc/Pila.h"
#include "../inc/Llave.h" 
#include "../inc/ExpresionJson.h" 
#include "../inc/Context.h"


String :: String(Valor *v){ valor = v;}

bool String :: validarExpresion(char c){
   if (c == '"' && p.pilavacia()){ 
        p.apilar(c);
        return true;
    }   
    if (c == '"' && !p.pilavacia()){ 
        p.desapilar();
        valor->setEstadoInterno(valor->getValor_listaString());
        return valor->getValor_listaString()->validarExpresion(c);
    }
    else if (!p.pilavacia()){
        return true;
    }
    return false;     
}

ListaString :: ListaString(Valor *v){ valor = v;}

bool ListaString :: validarExpresion(char c){
   if (c == '[' && p.pilavacia()){ 
        p.apilar(c);
        valor->setEstadoInterno(valor->getValor_string());
        return true;
    } else if (c == ']' && p.tope() == '['){ 
        p.desapilar();
        valor->getContext()->setEstado(valor->getContext()->getExpresionJson()); 
        valor->setEstadoInterno(nullptr);
        return true;     
    } else if (c == ',' && p.tope() == '[')
    {
         valor->setEstadoInterno(valor->getValor_string());
         return true;
    }  
    else if(p.pilavacia()){
        valor->getContext()->setEstado(valor->getContext()->getExpresionJson()); 
        valor->setEstadoInterno(nullptr);
        return true;  
    } else if (!p.pilavacia() && (c == '\n' || c == ' ' || c == '\t' || c == '"' ))
    {
        return true;
    }
    return false;     
}

bool Valor:: validarExpresion(char c){
    if (c == '\n' || c == ' ' || c == '\t' ){ return true;
    } 
    if (estadoInterno != nullptr)
    {
        if ( estadoInterno->getEstadoInterno() == getValor_listaString() ){ lista_string.agregar(c); }
        return estadoInterno->validarExpresion(c);
    }
    else if ( c == '"')
    {
        setEstadoInterno(getValor_string());
        p1.desapilar();
        return estadoInterno->validarExpresion(c);
    }else if ( c =='{')
    {
        getContext()->setEstado(getContext()->getExpresionJson());
        p1.desapilar();
        return getContext()->getExpresionJson()->validarExpresion(c);
    }
    else if ( c =='[')
    {
        setEstadoInterno(getValor_listaString());
        p1.desapilar();
        lista_string.agregar(c);
        return estadoInterno->validarExpresion(c);
    }
    cout<<endl;
    cout<<"valor no valida"<<endl;
    return false;
}

void Valor::guardarExpresion(char c){
   if(c == '\n' || c == ' ' || c == '\t' ){ return ; }
     expresion += c;
}

string Valor::print(){
    return expresion;
}





       

