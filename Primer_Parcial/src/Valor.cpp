#include <iostream>
#include <string>
#include <fstream>
using namespace std;    


#include "../inc/Estado.h" 
#include "../inc/ExpresionJson.h"



bool Valor:: validarExpresion(char c){
    if (valorDato != nullptr)
    {
        if(valorDato->getExpresionEsCorrecta()){
            getExpresionJson()->setEstado(getExpresionJson()->getEntreLlaves());
            valores.push_back(valorDato);
            valorDato = nullptr;
            return getExpresionJson()->getEntreLlaves()->validarExpresion(c);
        }
        return valorDato->validarExpresion(c);
    }
    else if ( c == '"')
    {
        valorDato = new String();
        return valorDato->validarExpresion(c);
    }
    else if ( c == '[')
    {
        valorDato = new ListaString();
        return valorDato->validarExpresion(c);    
    }
    else if ( c =='{')
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





       

