#include <iostream>
#include <string>
#include <fstream>
using namespace std;    


#include "../inc/Estado.h" 
#include "../inc/ExpresionJson.h"


bool Valor:: validarExpresion(char c){
    if (valorDato != nullptr)          // 
    {
        bool valida = valorDato->validarExpresion(c);  // Analiza la correctitud del valor, sin importar el tipo dato
        if( valorDato->getExpresionEsCorrecta() ){  
            valorDato = nullptr;
            getExpresionJson()->setEstado(getExpresionJson()->getEntreLlaves()); // Si es correcta vuelve al estado entre llaves 
        } 
        return valida;
    }
    if ( c == '"')          // El valor es de tipo string 
    {
        valorDato = new String();
        valores.encolar(valorDato);  // Se almacena el string en el buffer
        return valorDato->validarExpresion(c);
    }
    else if ( c == '[')     // El valor es de tipo lista string 
    {
        valorDato = new ListaString();
        valores.encolar(valorDato);  // Se almacena la lista de string en el buffer
        return valorDato->validarExpresion(c);    
    }
    else // ( c =='{')       
    {
        valores.encolar(new JsonAyed());
    //    getExpresionJson()->setEstado(getExpresionJson()->getEntreLlaves());  // Vuelve al estado entre llaves
        return getExpresionJson()->getEntreLlaves()->validarExpresion(c);  // El valor es una subexpresion
      //  return false;  // caracter incorrecto
    }
  //  expresion = c; // Guarda char invalido
   // return false;
}
  
string Valor::print(){
    if (valores.esvacia()) return "";
    ostringstream resultado ;
    if(dynamic_cast<JsonAyed*>(valores.last())){
        resultado << "";
    } else{
        resultado << valores.last()->print();  // Accede y procesa el primer elemento
    }
    delete valores.last();
    valores.borrar_last(); // Libera la memoria del objeto al que apunta el primer puntero
    return resultado.str();
}





       

