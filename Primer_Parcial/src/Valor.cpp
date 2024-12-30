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


ListaString :: ListaString(){ str = new String_();}

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
               expresionCorrecta = true;
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

bool ListaString :: getExpresionEsCorrecta(){
    return expresionCorrecta;
}

string ListaString :: print(){
    static int i = 0;
    for (int i = 0; i < strings.size(); i++)
    {
        cadena += strings.at(i).print();
    }
    return cadena;
}


bool Valor:: validarExpresion(char c){
    if (c == '\n' || c == ' ' || c == '\t' ) return true;
    if (valorDato != nullptr)
    {
        if(valorDato->getExpresionEsCorrecta()){
            getContext()->setEstado(getContext()->getExpresionJson());
            valores.push_back(valorDato);
            valorDato = nullptr;
            return getContext()->getExpresionJson()->validarExpresion(c);
        }
        return valorDato->validarExpresion(c);
    }
    else if ( c == '"')
    {
        tipo = STRING;
        valorDato = new String_();
        return valorDato->validarExpresion(c);
    }
    else if ( c == '[')
    {
        tipo = LISTA;
        valorDato = new ListaString();
        return valorDato->validarExpresion(c);    
   }
    else if ( c =='{')
    {
        getContext()->setEstado(getContext()->getExpresionJson());
        return getContext()->getExpresionJson()->validarExpresion(c);
    }
    return false;
}

string Valor::print(){
    static int i = 0;
    if (valores.empty()) return "";
    string resultado = valores[i++]->print();
    return resultado;
}





       

