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

bool Llave:: validarExpresion(char c){
    char comilla;
    expresion += c;
    if (c == '\n' || c == ' ' || c == '\t' ){ return true;
    }
    else if (c == '"' && p.pilavacia()){ 
        p.apilar(c);
        return true;     
    }
    else if (c == '"' && !p.pilavacia()){ 
        p.desapilar();
        ctx->setEstado(ctx->getValor());
        return true;     
    }
    else if (!p.pilavacia()){
        return true;
    }
    return false;
} 
    