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


ListaString :: ListaString(){ str = new String_();}

bool ListaString :: validarExpresion(char c){
    agregar(c);
    if (c == '[' && p.pilavacia()){ 
        p.apilar(c);
        cadena += c;
        return true;
    } 
    else if (p.tope() == '[')
    {
        if (str->getExpresionEsCorrecta()){
            cadena += c;
            strings.push_back(*str);
            delete str;
            str = new String_();
            if (c == ',')
            {
              return true;
            }
            else if (c == ']')
            {
               p.desapilar();
               expresionCorrecta = true;
               return true;
            }
            else{
                return false;
            }      
        }
        return str->validarExpresion(c);
    }
    return false;     
}

bool ListaString :: getExpresionEsCorrecta(){
    return expresionCorrecta;
}

string ListaString :: print(){
    ostringstream resultado;
    
    while (cadena.size()>1)
    {
        resultado << cadena.front() + strings.front().print(); 
        strings.erase(strings.begin());
        cadena.erase(cadena.begin());
        resultado << this->print();
    }
    return resultado.str() + cadena.front();
}


bool Valor:: validarExpresion(char c){
    if (valorDato != nullptr)
    {
        if(valorDato->getExpresionEsCorrecta()){
            getContext()->setEstado(getContext()->getExpresionJson());
            valores.push_back(valorDato);
            valorDato = nullptr;
            return getContext()->getExpresionJson()->validarExpresion(c);
        }
        return valorDato->validarExpresion(c);
    }
    else if ( c == '"')
    {
        valorDato = new String_();
        return valorDato->validarExpresion(c);
    }
    else if ( c == '[')
    {
        valorDato = new ListaString();
        return valorDato->validarExpresion(c);    
    }
    else if ( c =='{')
    {
        valorDato = new ExpresionJson();
        valores.push_back(valorDato);
        valorDato = nullptr;
        getContext()->setEstado(getContext()->getExpresionJson());
        return getContext()->getExpresionJson()->validarExpresion(c); 
    }
    return false;
}

string Valor::print(){
    if (valores.empty()) return "";
    ostringstream resultado;
    if(dynamic_cast<ExpresionJson*>(valores.front())){
      valores.erase(valores.begin()); 
      return "";
    }
    // Accede y procesa el primer elemento
    resultado << valores.front()->print(); 
    // Elimina el primer elemento
    valores.erase(valores.begin());  
    return resultado.str();
}





       

