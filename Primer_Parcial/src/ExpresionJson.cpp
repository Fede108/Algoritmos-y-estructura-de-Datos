#include <iostream>
#include <string>
#include <fstream>
using namespace std;    

#include "../inc/ExpresionJson.h" 
#include "../inc/State.h" 
#include "../inc/Llave.h" 
#include "../inc/Context.h"

ExpresionJson::ExpresionJson(Context *contexto){
    ctx = contexto;
}

bool ExpresionJson:: validarExpresion(char c){
    expresion += c;
    if(c == '\n' || c == ' ' || c == '\t' ){ return true; }
    else if(c=='{')
    {
        p.apilar('{');
        ctx->setEstado(ctx->getLlave());
        return true;
    }   
    else if (!p.pilavacia() && c==',')
    {
       ctx->setEstado(ctx->getLlave());
       return true;        
    }
    else if(c=='}') 
    {
       p.desapilar();
       return true;
    }
     return false;        
} 
    