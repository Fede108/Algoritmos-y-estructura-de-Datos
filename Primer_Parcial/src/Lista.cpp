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

bool Lista:: validarExpresion(char c){ /*
    expresion += c;
    if (c == '\n' || c == ' ' || c == '\t' ){ return true;
    }
    else if (c == ':'){
        p1.apilar(c);
        p2.apilar(c);
    }
    else if(c == '[' && p1.size() == 1 && p2.pilavacia()){     
        p1.apilar(c);
        return true;
    }
    else if(c == ']' && p2.size() == 2){
        if (p1.tope() == '[' )
        {
            p1.desapilar();
            p1.desapilar();
            return true;    
        }
        return false;    
    }
    else if (c == '"' && p2.tope() == ':'){
        p2.apilar(c);
        return true;     
    }
    else if (c == '"' && p2.tope() == '"'){
        p2.desapilar();
        if (p1.pilavacia())
        {
            ctx->setEstado(new ExpresionJson(ctx));    
        }
        return true;     
    } */
    return false;
} 
       

