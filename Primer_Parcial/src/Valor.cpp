#include <iostream>
#include <string>
#include <fstream>
using namespace std;    


#include "../inc/Estado.h" 
#include "../inc/ExpresionJson.h"


bool Valor:: validarExpresion(char c){
    if (componenteJson != nullptr)          // Si ya existe el valor se lo continua evaluando
    {
        bool valida = componenteJson->validarExpresion(c);  // Analiza la correctitud del valor, sin importar el tipo dato
        if( componenteJson->getExpresionEsCorrecta() ){  
            componenteJson = nullptr;
            getExpresionJson()->setEstado(getExpresionJson()->getEntreLlaves()); // Si es correcta vuelve al estado entre llaves 
        } 
        return valida;
    }
    // Se crea un nuevo valor segun el tipo de dato

    if ( c == '"')          // El valor es de tipo string 
    {
        componenteJson = new String();
        valores.encolar(componenteJson);  // Se almacena el string en el buffer
        return componenteJson->validarExpresion(c);
    }
    if ( c == '[')     // El valor es de tipo lista string 
    {
        componenteJson = new ListaString();
        valores.encolar(componenteJson);  // Se almacena la lista de string en el buffer
        return componenteJson->validarExpresion(c);    
    }
    if ( c =='{')  // El valor es de tipo subexpresion   
    {
        valores.encolar(new JsonAyed());
        return getExpresionJson()->getEntreLlaves()->validarExpresion(c);  // Se evalua el valor en clase entre llaves

    }
    caracterIncorrecto = c; // Guarda char invalido
    return false;
}
  
string Valor::print(){
    if (valores.esvacia()) return caracterIncorrecto + "";  // Si buffer de valores esta vacio el unico valor a retornar posible es caracter incorrecto

    ostringstream resultado ;
    if(dynamic_cast<JsonAyed*>(valores.last())){  // Si el valor guardado es de tipo subexpresion no retorna nada
        resultado << "";
    } else{
        resultado << valores.last()->print();  // Accede y procesa el primer elemento
    }
    delete valores.last();  // Libera la memoria del objeto 
    valores.desencolar();   // Elimina el elemento mas antiguo del buffer
    return resultado.str();
}





       

