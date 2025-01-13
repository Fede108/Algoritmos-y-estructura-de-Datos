#include "../inc/ComponenteJson.h"

bool String :: validarExpresion(char c){
    str += c;   // Agrega el carácter al buffer actual
    if (c == '"' && p.pilavacia()) { 
        p.apilar(c); 
        return true;
    } 
     // Si se cierran las comillas, la expresión es válida  
    if (c == '"' && !p.pilavacia()) { 
        p.desapilar(); 
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

        if (str == nullptr){ // no hay string a evaluar
            if (c == ']')  
            {  
                cadena += c;
                p.desapilar();
                expresionCorrecta = true;   
                return true;
            }
            // primer string de la lista
            if(strings.esvacia()){
                str = new String();
                strings.encolar(str);
            }
            // siguientes strings de la lista
            else if (c == ',')
            {
                cadena += c;
                str = new String();
                strings.encolar(str);
                return true;
            } else {
                cadena += c;
                return false;
            } 
            
        }
        // se continua validando el ultimo string
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

    if(cadena.size()>0 || !strings.esvacia()){

        if (cadena.size()>0)
        {
            resultado << cadena.front();
            cadena.erase(cadena.begin());
        }
        if (!strings.esvacia())
        {
            resultado << strings.last()->print(); 
            delete strings.last();
            strings.borrar_last();
        }

        resultado << this->print();

    }
 
    return resultado.str(); 
}
