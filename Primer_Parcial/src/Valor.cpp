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
        valores.push_back(valorDato);
        return valorDato->validarExpresion(c);
    }
    if ( c == '[')
    {
        valorDato = new ListaString();
        valores.push_back(valorDato);
        return valorDato->validarExpresion(c);    
    }
    if ( c =='{')
    {
        valores.push_back(new JsonAyed());
        getExpresionJson()->setEstado(getExpresionJson()->getEntreLlaves());
        return getExpresionJson()->getEntreLlaves()->validarExpresion(c); 
    }
    return false;
}
  
string Valor::print(){
    if (valores.empty()) return "";
    ostringstream resultado;
    if(dynamic_cast<JsonAyed*>(valores.front())){
      resultado << "";
    } else{
         // Accede y procesa el primer elemento
        resultado << valores.front()->print(); 
    }
    // Libera la memoria del objeto al que apunta el primer puntero
    delete valores.front(); 
    // Elimina el primer elemento
    valores.erase(valores.begin());  
    return resultado.str();
}





       

