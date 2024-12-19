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
void ExpresionJson:: validarExpresion(char c){
    expresion += c;
    if(c == '\n' || c == ' ' || c == '\t' ){}
    else if(c=='{'){
            p.apilar('{');
    }
    else if (!p.pilavacia() && c=='"')
    {
       ctx->setEstado(new Llave(ctx));        
    }
    else if(c=='}') {
       p.desapilar();
       ctx->setEstado(new ExpresionJson(ctx));  
    }        
} 
    