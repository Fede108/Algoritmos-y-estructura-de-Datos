
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

#include "../inc/Pila.h"
#include "../inc/Expresion.h"
#include "../inc/Llave_valor.h"
#include "../inc/Cola.h"


void lector_linea(int indice,string cadena,Cola<string>* l);
void analizador_linea(Cola<string>* l);  

int main()
{ 
  ifstream archivo("data_json.txt");
  Cola<string>* l = new Cola<string>();
  string cadena;
  bool linea_nueva = false;
    if (archivo.is_open()) {
        char c;
        while (archivo.get(c)) { 
            if(c == '\n') { linea_nueva = !linea_nueva;}
            if (linea_nueva)
            {
               lector_linea(1,cadena,l);
               cadena = "";     
               linea_nueva = false;
            }  
              cadena += c;           
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1; 
    }

    lector_linea(0,cadena,l);  
    analizador_linea(l);
}

void lector_linea(int indice, string cadena, Cola<string>* l){
    if (cadena.length() == 0) return;
    if (indice == cadena.length())
    {
        string linea = cadena.substr(0,indice); 
        l->encolar(linea);
        return;
    }
    lector_linea(indice + 1, cadena, l);
}

void analizador_linea(Cola<string>* l){
    if (l->colavacia())
    {
        return;
    }
    Expresion* e = new Llave_valor(l->tope());
    if (l->resto()->colavacia())
    {
        cout<<e->validar_ultimaLinea()<<endl; 
        cout<<e->guardarLinea()<<endl;
    }else{
        cout<<e->validar_linea()<<endl;
        cout<<e->guardarLinea()<<endl;
    }
    analizador_linea(l->resto());
}