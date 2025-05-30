#include <iostream>
#include <string>
#include <fstream>
using namespace std;    


#include "../inc/Estado.h" 
#include "../inc/ExpresionJson.h"


bool Valor:: validarExpresion(char c){
    if (componenteJson != nullptr)          // si ya existe el valor se lo continua evaluando
    {
        bool valida = componenteJson->validarExpresion(c);  // analiza la correctitud del valor, sin importar el tipo dato
        if( componenteJson->getExpresionEsCorrecta() ){  
            componenteJson = nullptr;
            getExpresionJson()->setEstado(getExpresionJson()->getEntreLlaves()); // si es correcta vuelve al estado entre llaves 
        } 
        return valida;
    }
    // se crea un nuevo valor segun el tipo de dato

    if ( c == '"')          // el valor es de tipo string 
    {
        componenteJson = new String();
        bufferComponentes.encolar(componenteJson);  // se almacena el string en el buffer
        return componenteJson->validarExpresion(c);
    }
    if ( c == '[')     // el valor es de tipo lista string 
    {
        componenteJson = new ListaString();
        bufferComponentes.encolar(componenteJson);  // se almacena la lista de string en el buffer
        return componenteJson->validarExpresion(c);    
    }
    if ( c =='{')  // el valor es de tipo subexpresion json   
    {
        bufferComponentes.encolar(new JsonAyed());
        return getExpresionJson()->getEntreLlaves()->validarExpresion(c);  // se evalua el valor en clase entre llaves
    }
    caracterIncorrecto = c; // guarda char invalido
    return false;
}
  
string Valor::print(){
    if (bufferComponentes.esvacia()) return caracterIncorrecto + "";  // el unico valor a retornar posible es un caracter incorrecto

    ostringstream resultado ;
    if(dynamic_cast<JsonAyed*>(bufferComponentes.last())){  // si el valor guardado es de tipo subexpresion retorna string vacio
        resultado << "";
    } else{
        resultado << bufferComponentes.last()->print();  // retorna el valor mas antiguo en el buffer
    }
    delete bufferComponentes.last();  // libera la memoria del objeto 
    bufferComponentes.desencolar();   // elimina el valor mas antiguo del buffer
    resultado << getExpresionJson()->getEntreLlaves()->print();
    return resultado.str();
}





       

