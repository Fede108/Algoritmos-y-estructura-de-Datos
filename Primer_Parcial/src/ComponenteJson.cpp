#include "../inc/ComponenteJson.h"

bool String :: validarExpresion(char c){
    str += c;   // se agrega el caracter al buffer
    if (c == '"' && p.pilavacia()) { 
        p.apilar(c); 
        return true;
    } 
     // si se cierran las comillas la expresion es correcta  
    if (c == '"' && !p.pilavacia()) { 
        p.desapilar(); 
        expresionCorrecta = true;
        return true;
    }
    if (!p.pilavacia()){ // cualquier caracter dentro de las comillas es valido
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
            if(bufferStrings.esvacia()){
                str = new String();
                bufferStrings.encolar(str);
            }
            // siguientes bufferStrings de la lista
            else if (c == ',')
            {
                cadena += c;
                str = new String();
                bufferStrings.encolar(str);
                return true;
            // cualquier otro caracter es incorrecto
            } else {
                cadena += c;
                return false;
            } 
            
        }
        // se continua validando el ultimo string
        bool valida = str->validarExpresion(c);
        if (str->getExpresionEsCorrecta()){  // el string se completo de manera correcta
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

    if(cadena.size()>0 || !bufferStrings.esvacia()){   // se recorre de manera recursiva cadena y bufferString
        if (cadena.size()>0)
        {
            resultado << cadena.front();
            cadena.erase(cadena.begin());
        }
        if (!bufferStrings.esvacia())
        {
            resultado << bufferStrings.last()->print(); 
            delete bufferStrings.last();   // se libera la memoria del puntero al objeto String
            bufferStrings.borrar_last();   // se elimina de la lista
        }

        resultado << this->print();  // resultado almacena los caracteres de la lista de strings
    }
 
    return resultado.str(); 
}
