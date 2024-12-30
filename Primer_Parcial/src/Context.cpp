#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

#include "../inc/State.h"
#include "../inc/Context.h"
#include "../inc/ExpresionJson.h" 
#include "../inc/Llave.h" 
#include "../inc/Valor.h" 


void Context :: setEstado(State* estado){
        estadoActual = estado;
        estadoActual->setContext(this);
}

bool Context :: leer_archivo(string nombre_archivo){
    bool correcto = true;
    ifstream archivo(nombre_archivo);
    if (archivo.is_open() ) {
        char c;
        while(archivo.get(c) && correcto){
            correcto = estadoActual->validarExpresion(c);
        }
      //  correcto = expresionJson.validarJson();
      //  cout<<endl;
      //  cout<<correcto<<endl;
    }
    
    for (int i = 0; i < expresionJson.size() ; i++)
    {
        json += estadoActual->print();
    }
    cout<<json<<endl;
    return correcto;
}
