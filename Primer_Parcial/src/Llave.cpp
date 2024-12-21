#include <iostream>
#include <string>
#include <fstream>
using namespace std;    

#include "../inc/Llave.h" 
#include "../inc/State.h" 
#include "../inc/Valor.h" 
#include "../inc/ExpresionJson.h" 
#include "../inc/Context.h"





bool Llave:: validarExpresion(char c){
    if (c == '\n' || c == ' ' || c == '\t' ){ return true;
    }
    if (c == '"' && p.size()<2){ 
        p.apilar(c);
        return true;     
    }
    else if (c == ':' && p.size() == 2)
    {
        p.desapilar();
        p.desapilar();
        getContext()->setEstado(getContext()->getValor());
        return true;
    }     
    else if (p.size() == 1 && p.tope() == '"'){
        return true;
    }
    cout<<endl;
    cout<<"llave no valida"<<endl;
    return false;
}

void Llave::guardarExpresion(char c){
   if(c == '\n' || c == ' ' || c == '\t' ){ return ; }
     expresion += c;
}

string Llave::print(){
    return expresion;
}
    