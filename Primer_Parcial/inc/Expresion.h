#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace std;

#ifndef EXPRESION_H
#define EXPRESION_H
template <class T> class Expresion
{
private:
    string cadena;
    Pila<char> p;
    string *buffer;
    int posicion;
public:  
    Expresion(string cadena) : cadena(cadena) {};
    bool llave(char prefijo, char abierto, char cerrado);
    int getPosSeparador();
    virtual bool validar();
    virtual bool validar_ultimaLinea();
    void setCadena(string cadena); 
    string getCadena();
    bool separador(char s);
};

template <class T>  bool Expresion<T>::validar(){return false;}
template <class T>  bool Expresion<T>::validar_ultimaLinea(){return false;}


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

template <class T> void Expresion<T>::  guardarCadena(){

}

#endif