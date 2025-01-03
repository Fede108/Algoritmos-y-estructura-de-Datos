#include "../inc/Dato.h"

bool String :: validarExpresion(char c){
    str += c;
    if (c == '"' && p.pilavacia()) { 
        p.apilar(c); // Abre una comilla
        return true;
    }   
    if (c == '"' && !p.pilavacia()) { 
        p.desapilar(); // Cierra una comilla
        expresionCorrecta = true;
        return true;
    }
    if (!p.pilavacia()){ // Cualquier caracter dentro de las comillas es valido
        return true;
    }
    return false;    
}

bool String :: getExpresionEsCorrecta(){
    return expresionCorrecta;
}

string String ::print(){
    return str;
}

//-------------------------------------------------------------------------------

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
            str = new String();
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
    
    if (cadena.size()>1)
    {
        resultado << cadena.front() + strings.front().print(); 
        strings.erase(strings.begin());
        cadena.erase(cadena.begin());
        resultado << this->print();
        return resultado.str();
    }
    return resultado.str() + cadena.front();
}
