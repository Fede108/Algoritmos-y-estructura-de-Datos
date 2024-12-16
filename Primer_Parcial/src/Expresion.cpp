
#include "Pila.h"
#include "Lista.h"
using namespace std;

template <class T> class Expresion
{
private:
    Pila<T> p;
    T *buffer;
//   string cadena;
 //  char abierto; 
//   char cerrado;
    int posicion;
public:  
      Expresion();
//    bool comillas( string cadena;);
//    bool separador(char separador);
    bool llave(string cadena, char prefijo, char abierto, char cerrado);
    int getPosicion();
};
template <class T> Expresion<T>::Expresion() {}

template <class T> bool Expresion<T>::llave(string cadena, char prefijo, char abierto, char cerrado){
    int indice = 0;
    if(cadena.at(0) ==  prefijo){
        if(cadena.at(1) ==  abierto){   p.apilar(cadena.at(1));
            while ( indice<cadena.length() || p.pilavacia() )
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

/*template <class T> bool Expresion<T>:: separador(char separador){
    return cadena.at(posicion) == separador;
}*/

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
    if(llave(cadena, '/n','"','"')){
        string valor = cadena.substr(getPosicion());
        return llave(valor,':','"','"') && cadena.at(getPosicion()) == ',' ;                   
    } 
    return false;
}

//-----------------------------------------------------

int main()
{ 
  Lista<string>* l = new Lista<string>();
  string cadena;
  cout<<endl<<"Ingrese cadena= "; cin>>cadena;
  lector_linea(0,cadena,l);  
  
  llave_valor<string>* p = new llave_valor<string>(l->cabeza());
  p->validar();
}

void lector_linea(int indice, string cadena, Lista<string>* l){
    if (indice == cadena.length())
    {
        return;
    }
    if (cadena.at(indice) == '/n')
    {
        string linea = cadena.substr(0,indice); 
        l->add(linea);
        cadena = cadena.substr(indice); 
        indice = 0;
    } 
    lector_linea(indice + 1, cadena, l);
}