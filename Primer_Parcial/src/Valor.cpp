#include <iostream>
#include <string>
#include <fstream>
using namespace std;    


#include "../inc/Estado.h" 
#include "../inc/ExpresionJson.h"


bool Valor:: validarExpresion(char c){
    if (valorDato != nullptr)          // Si ya existe el valor se lo continua evaluando
    {
        bool valida = valorDato->validarExpresion(c);  // Analiza la correctitud del valor, sin importar el tipo dato
        if( valorDato->getExpresionEsCorrecta() ){  
            valorDato = nullptr;
            getExpresionJson()->setEstado(getExpresionJson()->getEntreLlaves()); // Si es correcta vuelve al estado entre llaves 
        } 
        return valida;
    }
    // Se crea un nuevo valor segun el tipo de dato

    if ( c == '"')          // El valor es de tipo string 
    {
        valorDato = new String();
        valores.encolar(valorDato);  // Se almacena el string en el buffer
        return valorDato->validarExpresion(c);
    }
    if ( c == '[')     // El valor es de tipo lista string 
    {
        valorDato = new ListaString();
        valores.encolar(valorDato);  // Se almacena la lista de string en el buffer
        return valorDato->validarExpresion(c);    
    }
    if ( c =='{')  // El valor es de tipo subexpresion   
    {
        valores.encolar(new JsonAyed());
        return getExpresionJson()->getEntreLlaves()->validarExpresion(c);  // Se evalua el valor en clase entre llaves

    }
    expresion = c; // Guarda char invalido
    return false;
}
  
string Valor::print(){
    if (valores.esvacia()) return expresion + "";

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





       

