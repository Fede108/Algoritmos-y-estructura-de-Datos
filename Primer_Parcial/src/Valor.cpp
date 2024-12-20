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

Valor :: Valor(Context *contexto){ ctx = contexto;}

bool Valor:: validarExpresion(char c){
    expresion += c;
    if (c == '\n' || c == ' ' || c == '\t' ){ return true;
    }
    else if (c == ':' && p1.pilavacia()){
        p1.apilar(c);
        return true;
    } 
    else if (c == '"' && p1.tope() == ':'){
        p1.desapilar();
        p1.apilar(c);
        return true;     
    }
    else if (c == '"' && p1.tope() == '"'){
        p1.desapilar();
        ctx->setEstado(ctx->getExpresionJson());    
        return true;     
    }
    else if(p1.tope() == '"'){ 
        return true;
    } 
    
    return false;
}

class ListaString
{
private:
    Pila<char> p;
    String string;
public:
   void validarListaString(char c);
};


class String
{
private:
    Pila<char> p;
public:
    void validarString(char c);
};





       

