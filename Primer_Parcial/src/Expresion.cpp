
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
    string cadena;
    Pila<char> p;
    T *buffer;
    int posicion;
public:  
    Expresion(string cadena) : cadena(cadena) {};
    bool llave(char prefijo, char abierto, char cerrado);
    int getPosSeparador();
    virtual bool validar();
    void setCadena(string cadena); 
    string getCadena();
    bool separador(char s);
};
//template <class T> Expresion<T>::Expresion(string cadena) : cadena(cadena) {}

template <class T>  bool Expresion<T>::validar(){return false;}

template <class T> bool Expresion<T>::llave( char prefijo, char abierto, char cerrado){
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

template <class T> int Expresion<T>:: getPosSeparador(){
    return posicion;
}

template <class T> bool Expresion<T>:: separador(char s){
    if (cadena.length() - 1 < getPosSeparador()) { return false; }
    if (cadena.at(getPosSeparador()) == s){ return true; }
    return false;    
}

template <class T> void Expresion<T>::  setCadena(string cadena){
    this->cadena = cadena;
}

template <class T> string Expresion<T>::  getCadena(){
    return cadena;  
}
//------------------------------------------------------

template <class T> class llave_valor : public Expresion<T> {
    private:
      
    public:
        llave_valor(string cadena): Expresion<T>(cadena) {}
        bool validar();
};

template <class T> bool llave_valor<T> :: validar(){
    if(this->llave('\n','"','"')){
        string valor = this->getCadena().substr(this->getPosSeparador());
        this->setCadena(valor);
        return  this->llave(':','"','"') && this->separador(',') ;                   
    } 
    return false;
}
//

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
    Expresion<string>* e = new llave_valor<string>(l->cabeza());
    cout<<e->validar()<<endl;
    analizador_linea(l->resto());
}