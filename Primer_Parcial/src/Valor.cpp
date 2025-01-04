#include <iostream>
#include <string>
#include <fstream>
using namespace std;    


#include "../inc/Estado.h" 
#include "../inc/ExpresionJson.h"


bool Valor:: validarExpresion(char c){
    if (valorDato != nullptr)
    {
        bool valida = valorDato->validarExpresion(c);
        if( valorDato->getExpresionEsCorrecta() ){  
            valorDato = nullptr;
            getExpresionJson()->setEstado(getExpresionJson()->getEntreLlaves());
        } 
        return valida;
    }
    if ( c == '"')
    {
        valorDato = new String();
        valores.encolar(valorDato);
        return valorDato->validarExpresion(c);
    }
    if ( c == '[')
    {
        valorDato = new ListaString();
        valores.encolar(valorDato);
        return valorDato->validarExpresion(c);    
    }
    if ( c =='{')
    {
        valores.encolar(new JsonAyed());
        getExpresionJson()->setEstado(getExpresionJson()->getEntreLlaves());
        return getExpresionJson()->getEntreLlaves()->validarExpresion(c); 
    }
    expresion = c; // Guarda char invalido
    return false;
}
  
string Valor::print(){
    if (valores.esvacia()) return expresion + "";
    ostringstream resultado;
    if(dynamic_cast<JsonAyed*>(valores.last())){
        resultado << "";
    } else{
        resultado << valores.last()->print();  // Accede y procesa el primer elemento
    }
    delete valores.last();
    valores.borrar_last(); // Libera la memoria del objeto al que apunta el primer puntero
    return expresion + resultado.str();
}





       

