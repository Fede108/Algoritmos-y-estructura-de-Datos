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


/*void Valor::apilar(char c){
    p.apilar(c);
    void Valor::guardar(string comando){
    expresion += comando;
    
bool Valor::pilavacia(){
    return p.pilavacia();
}
    void Valor::desapilar(){
    p.desapilar();
}
} 
} */

Valor :: Valor(Context *contexto){ ctx = contexto;}

void Valor:: validarExpresion(char c){
    expresion += c;
    if (c == '\n' || c == ' ' || c == '\t' ){
    }
    else if (c == '"'  && p.pilavacia()){ 
        p.apilar(c);
    }
    else if (c == ',' && ! p.pilavacia()){ 
        p.desapilar();
        ctx->setEstado(new Llave(ctx));  
    }
    else if(c=='}') {
       ctx->setEstado(new ExpresionJson(ctx));  
    }
} 
       

