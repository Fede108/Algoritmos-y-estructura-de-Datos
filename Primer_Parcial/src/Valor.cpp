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


String :: String(Valor *v){ 
    valor = v;
    str = new String_();
    }

bool String :: validarExpresion(char c){
    bool correcta = str->validarExpresion(c);
    if (str->getExpresionEsCorrecta())
    {   
        str = new String_();
        valor->getContext()->setEstado(valor->getContext()->getExpresionJson()); 
        valor->setEstadoInterno(nullptr);
    }
    return correcta;
}

ListaString :: ListaString(Valor *v){ valor = v; str = new String_();}

bool ListaString :: validarExpresion(char c){
    agregar(c);
    if (c == '[' && p.pilavacia()){ 
        p.apilar(c);
        return true;
    } 
    else if (p.tope() == '[')
    {
        if (str->getExpresionEsCorrecta()){
            str = new String_();
            if (c == ',')
            {
              return true;
            }
            else if (c == ']')
            {
               p.desapilar();
               valor->getContext()->setEstado(valor->getContext()->getExpresionJson()); 
               valor->setEstadoInterno(nullptr);
               return true;
            }
            else{
                return false;
            }      
        }
        return str->validarExpresion(c);
    }
    return false;     
}

bool Valor:: validarExpresion(char c){
    if (c == '\n' || c == ' ' || c == '\t' ) return true;
    if (estadoInterno != nullptr)
    {
        return estadoInterno->validarExpresion(c);
    }
    else if ( c == '"')
    {
        setEstadoInterno(getValor_string());
        return estadoInterno->validarExpresion(c);
    }
    else if ( c =='[')
    {
        setEstadoInterno(getValor_listaString());
        lista_string.agregar(c);
        return estadoInterno->validarExpresion(c);
    }
    else if ( c =='{')
    {
        getContext()->setEstado(getContext()->getExpresionJson());
        return getContext()->getExpresionJson()->validarExpresion(c);
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





       

