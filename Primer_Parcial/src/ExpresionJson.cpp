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
    correcto = true;
    ifstream archivo(nombre_archivo);
    if (archivo.is_open() ){
        char c;
        while(archivo.get(c) && correcto){
            if (c != '\n' && c != ' ' && c != '\t' ){
                correcto = estadoActual->validarExpresion(c);
                caracter++;
            } 
        }
    }

    if (correcto)
    {
        if(!entreLlaves.validarJson() || ! valor.validarValor()){  
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
    string marcador; 
    ofstream archivoSalida("salida_json");
       if (archivoSalida.is_open()) {
         if (correcto) {
            archivoSalida << json << "\nJSON correcto";
        } else{
            for (int i = 0; i < caracter - 1; i++)
            {
                marcador += " ";
            }
            marcador += "^";
            archivoSalida << json << "\n" <<  marcador;
        }
        archivoSalida.close();
    }
} 
