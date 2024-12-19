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
#include "../inc/Lista.h"


Lista :: Lista(Context *contexto){ ctx = contexto;}

void Lista:: validarExpresion(char c){
    expresion += c;
    if (c == '\n' || c == ' ' || c == '\t' ){
    }
    else if (c == '['  && p.pilavacia()){ 
        p.apilar(c);
    } 
    else if (c == '"' && !p.pilavacia())
    {
        ctx->setEstado(new Llave(ctx));
    }
    else if (c == '"' && p.pilavacia()){ 
        ctx->setEstado(new Valor(ctx));  
    }
    else if(c=='}') {
       ctx->setEstado(new ExpresionJson(ctx));  
    }
} 
       

