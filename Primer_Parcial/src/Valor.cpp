#include <iostream>
#include <string>
#include <fstream>
using namespace std;    

#include "../inc/Valor.h" 



void Valor::apilar(char c){
    p.apilar(c);
}

void Valor::desapilar(){
    p.desapilar();
}

bool Valor::pilavacia(){
    return p.pilavacia();
}

void Valor::guardar(string comando){
    expresion += comando;
}

bool Valor::evaluar_llave(char c ){
    expresion += c;
    if (c == '"'  && p.tope() != '"' ){ 
        p.apilar(c);
        return false;
    }
    if (c == '"' && p.tope() == '"' ){ 
        p.desapilar();
        return true;
    }
    return false;
} 
/* 
                    else if (c == '"' && llave_valor.pilavacia() && modo_valor){
                            llave_valor.guardar(comando);
                            llave_valor.apilar(c);
                    }
                    else if (!llave_valor.pilavacia()){
                            comando += c;                    
                            if (c == '"')
                            {   
                                llave_valor.guardar(comando);
                                llave_valor.desapilar();
                                modo_valor = false; 
                                                     
                            }
                    */

