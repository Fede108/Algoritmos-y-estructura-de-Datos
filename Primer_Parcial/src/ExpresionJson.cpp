#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

#include "../inc/Estado.h"
#include "../inc/ExpresionJson.h"

// cambia el modo de evaluacion de la expresion 
void ExpresionJson :: setEstado(Estado* estado){
        estadoActual = estado;
        estadoActual->setExpresionJson(this);
}

bool ExpresionJson :: leer_archivo(string nombre_archivo){
    correcto = true;
    ifstream archivo(nombre_archivo);
    if (archivo.is_open() ){
        char c;
        while(archivo.get(c) && correcto){    // lee los caracteres del archivo de a uno mientras sea correcto
            if (c != '\n' && c != ' ' && c != '\t' ){
                correcto = estadoActual->validarExpresion(c);   // determina la validez del caracter
                caracter++;
            } 
        }
    }

    if (correcto)   
    {
    // se evalua si las expresiones cerraron correctamente 
        if(!entreLlaves.pilaVacia() || ! valor.pilaVacia()){  
            caracter++;
            correcto = false;
        }    
    }
   
    setEstado(getEntreLlaves());
    while (entreLlaves.size()>0)
    {
        json += estadoActual->print();
    }
    
    return correcto;
}

void ExpresionJson :: generar_archivo(){
    cout << "Longitud de json calculada: " << json.length() << endl;
    string marcador = ""; 
    ofstream archivoSalida("salida.json");
       if (archivoSalida.is_open()) {
         if (correcto) {
            archivoSalida << json << "\nJSON correcto";
        } else{
            for (int i = 0; i < caracter-1; i++)
            {
                marcador += " ";
            }
            marcador += "^";
            archivoSalida << json << "\n" <<  marcador;
        }
        archivoSalida.close();
    }
} 
