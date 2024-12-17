
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

template <class T> class Llave_valor : public Expresion<T> {
    private:
      
    public:
        Llave_valor(string cadena): Expresion<T>(cadena) {}
        bool validar();
        bool validar_ultimaLinea();
};

template <class T> bool Llave_valor<T> :: validar_ultimaLinea(){
    if(this->llave('\n','"','"')){
        string valor = this->getCadena().substr(this->getPosSeparador());
        this->setCadena(valor);
        return  this->llave(':','"','"') && ! this->separador(',') ;                   
    } 
    return false;
}

template <class T> bool Llave_valor<T> :: validar(){ 
    if(this->llave('\n','"','"')){
        string valor = this->getCadena().substr(this->getPosSeparador());
        this->setCadena(valor);
        return  this->llave(':','"','"') && this->separador(',') ;                   
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
    Expresion<string>* e = new Llave_valor<string>(l->cabeza());
    if (l->resto()->esvacia())
    {
        cout<<e->validar_ultimaLinea()<<endl;    
    } else{
        cout<<e->validar()<<endl;
    }
    analizador_linea(l->resto());
}