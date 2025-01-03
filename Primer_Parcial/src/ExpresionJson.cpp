#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

#include "../inc/Estado.h"
#include "../inc/ExpresionJson.h"


void ExpresionJson :: setEstado(Estado* estado){
        estadoActual = estado;
        estadoActual->setExpresionJson(this);
}

bool ExpresionJson :: leer_archivo(string nombre_archivo){
    bool correcto = true;
    ifstream archivo(nombre_archivo);
    if (archivo.is_open() ){
        char c;
        while(archivo.get(c) && correcto){
            if (c != '\n' && c != ' ' && c != '\t' ){
                correcto = estadoActual->validarExpresion(c);
            } 
        }
    }

    correcto = correcto & llave.validarLlave() & valor.validarValor() & entreLlaves.validarJson(); 
    
    setEstado(getEntreLlaves());
    while (entreLlaves.size()>0)
    {
        json += estadoActual->print();
    }
    
    cout<<json<<endl;
    return correcto;
}
