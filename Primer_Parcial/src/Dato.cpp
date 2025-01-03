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
    if (p.tope() == '[')
    {

        if (str == nullptr){
            cadena += c;
            if (c == ']')
            {
               p.desapilar();
               expresionCorrecta = true;
               return true;
            }
            if(strings.empty()){
                str = new String();
                strings.push_back(str);
            }
            else if (c == ',')
            {
                str = new String();
                strings.push_back(str);
                return true;
            } else {
                return false;
            } 
            
        }
       
        bool valida = str->validarExpresion(c);
        if (str->getExpresionEsCorrecta()){
            str = nullptr;
        }          
        return valida;
    }
    return false;     
}

bool ListaString :: getExpresionEsCorrecta(){
    return expresionCorrecta;
}

string ListaString :: print(){
    ostringstream resultado;
    
    if (cadena.size()>1 && !strings.empty())
    {
        resultado << cadena.front() + strings.front()->print(); 
        delete strings.front();
        strings.erase(strings.begin());
        cadena.erase(cadena.begin());
        resultado << this->print();
        return resultado.str();
    }

    if(strings.size()==1){
        resultado << cadena.front() << strings.front()->print();
        strings.erase(strings.begin());
        return resultado.str();
    }
    return resultado.str() + cadena.front();
}
