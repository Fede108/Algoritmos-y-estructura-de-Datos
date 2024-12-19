#include <iostream>
#include <string>
#include <fstream>
using namespace std;    

#include "../inc/Llave.h" 
#include "../inc/State.h" 
#include "../inc/Valor.h" 
#include "../inc/ExpresionJson.h" 
#include "../inc/Context.h"
#include "../inc/Lista.h"

Llave ::Llave(Context *contexto){ ctx = contexto;}

void Llave:: validarExpresion(char c){
    expresion += c;
    if (c == '\n' || c == ' ' || c == '\t' ){
    }
    else if (c == '"'  && p.pilavacia() ){ 
        p.apilar(c);     
    }
    else if (c == '"'  && !p.pilavacia() ){ 
        p.desapilar();     
    }
    else if (c == ':' &&  !p.pilavacia() ){ 
        p.desapilar();
          ctx->setEstado(new Lista(ctx));  
    }
    else if(c=='}') {
          ctx->setEstado(new ExpresionJson(ctx));  
    }
} 
    