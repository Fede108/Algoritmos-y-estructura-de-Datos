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
    return correcto;
}

void ExpresionJson :: generar_archivo(){
    setEstado(getEntreLlaves());
    json = estadoActual->print();

    if(correcto) cout << "Expresion correcta" << endl;
    else cout << "Error en la expresion en el caracter " << caracter << endl;

    string marcador = ""; 
    ofstream archivoSalida("salida.json");
       if (archivoSalida.is_open()) {
         if (correcto) {
            archivoSalida << json << "\n JSON-AYED Valido";
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
