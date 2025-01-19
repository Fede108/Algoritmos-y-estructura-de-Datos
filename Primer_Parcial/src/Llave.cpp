#include <iostream>
#include <string>
#include <fstream>
using namespace std;    

#include "../inc/Estado.h" 
#include "../inc/ExpresionJson.h"


bool Llave :: validarExpresion(char c){
    
    if (str == nullptr)
    {
        str = new String();
        strings.encolar(str);
    }
    
    if (str->getExpresionEsCorrecta())  // string ingresado es correcto 
    {   str = nullptr;
        llaves += c; // guarda el caracter
        if (c == ':')
        { 
            // llave correcta
            getExpresionJson()->setEstado(getExpresionJson()->getValor()); // siguiente modo a validar es un valor   
            return true;
        }
            return false; // error, no hay : después de un string valido
    }

    return str->validarExpresion(c); // continua validando el string actual
}

string Llave :: print(){
    ostringstream resultado;
    if (!strings.esvacia())     resultado << strings.last()->print();
    if (!llaves.empty())        resultado << llaves.front();
                                resultado << getExpresionJson()->getValor()->print();

    
    if (!llaves.empty())  llaves.erase(llaves.begin());
    if (!strings.esvacia()){ delete strings.last();
    strings.borrar_last(); // elimina el primer elemento
    }
    return resultado.str();
}



