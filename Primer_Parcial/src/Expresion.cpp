
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

#include "../inc/Pila.h"
#include "../inc/Lista.h"


template <class T> class Expresion
{
private:
    Pila<char> p;
    T *buffer;
    int posicion;
public:  
      Expresion();
    bool llave(string cadena, char prefijo, char abierto, char cerrado);
    int getPosicion();
};
template <class T> Expresion<T>::Expresion() {}

template <class T> bool Expresion<T>::llave(string cadena, char prefijo, char abierto, char cerrado){
    int indice = 2;
    if(cadena.length()<4) return false;
    if(cadena.at(0) ==  prefijo){
        if(cadena.at(1)  ==  abierto){   p.apilar(cadena.at(1));
            while ( indice<cadena.length() && ! p.pilavacia() )
            {
                if(cadena.at(indice) == cerrado){
                   p.desapilar();
                   posicion = indice + 1;
                }
                indice++;   
            }
            return p.pilavacia();
        }
    }   
    return false;    
}

template <class T> int Expresion<T>:: getPosicion(){
    return posicion;
}

//------------------------------------------------------

template <class T> class llave_valor : public Expresion<T> {
    private:
    //    char separador;
        string cadena;
    public:
        llave_valor(string cadena) : cadena(cadena) {  Expresion<T>(); }  
        bool validar();
};

template <class T> bool llave_valor<T> :: validar(){
    if(this->llave(cadena, '\n','"','"')){
        string valor = cadena.substr(this->getPosicion());
        return  this->llave(valor,':','"','"') && valor.at(this->getPosicion()) == ',' ;                   
    } 
    return false;
}
//

//-----------------------------------------------------

void lector_linea(int indice,string cadena,Lista<string>* l);  

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
    llave_valor<string>* p = new llave_valor<string>(l->cabeza());
    cout<<p->validar()<<endl;
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