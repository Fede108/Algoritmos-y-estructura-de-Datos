
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

#include "../inc/Pila.h"
#include "../inc/Lista.h"
#include "../inc/Expresion.h"


//------------------------------------------------------

class Llave_valor : public Expresion{
    private:
       string cadena_llave;
       string cadena_valor; 
    public:
        Llave_valor(string linea): Expresion(linea) {}
        bool validar();
        bool validar_ultimaLinea();
};

bool Llave_valor :: validar(){
    cadena_llave = this->getLinea().substr(0, this->getPosSeparador());
    cadena_valor = this->getLinea().substr(this->getPosSeparador());
    if (verificarExpresion(cadena_llave,'\n','"','"') && verificarExpresion(cadena_valor,':','"','"'))
    {
        return cadena_valor[cadena_valor.length() - 1] == ',' && cadena_valor[cadena_valor.length() - 2] == '"';
    }              
    return false;
}

bool Llave_valor :: validar_ultimaLinea(){ 
    cadena_llave = this->getLinea().substr(0, this->getPosSeparador());
    cadena_valor = this->getLinea().substr(this->getPosSeparador());
    if (verificarExpresion(cadena_llave,'\n','"','"') && verificarExpresion(cadena_valor,':','"','"'))
    {
        return cadena_valor[cadena_valor.length() - 1] == '"' ;
    }                 
    return false;
}



//-----------------------------------------------------

void lector_linea(int indice,string cadena,Lista<string>* l);
void analizador_linea(Lista<string>* l);  

int main()
{ 
  ifstream archivo("data_json.txt");
  Lista<string>* l = new Lista<string>();
  string cadena;
  bool linea_nueva = true;
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

void lector_linea(int indice, string cadena, Lista<string>* l){
    if (indice == cadena.length())
    {
        string linea = cadena.substr(0,indice); 
        l->add(linea);
        return;
    }
    lector_linea(indice + 1, cadena, l);
}

void analizador_linea(Lista<string>* l){
    if (l->esvacia())
    {
        return;
    }
    Expresion* e = new Llave_valor(l->cabeza());
    if (l->resto()->esvacia())
    {
        cout<<e->validar_ultimaLinea()<<endl; 
        cout<<e->guardarLinea()<<endl;
    } else{
        cout<<e->validar()<<endl;
        cout<<e->guardarLinea()<<endl;
    }
    analizador_linea(l->resto());
}