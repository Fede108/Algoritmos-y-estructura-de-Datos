#include <string>
#include <iostream>
#include <fstream>
#include <vector>


#include "State.h"
#include "Pila.h" 
#include "Cola.h"
#include "Llave.h"

using namespace std;    

class Context; 
class Valor;

#ifndef VALOR_H
#define VALOR_H


class ListaString: public Dato
{
private:
    bool expresionCorrecta = false;
    Pila<char> p;
    Cola<char> cola;
    vector <String_> strings; //BUFFER
    String_ *str;  
    string cadena;
public:
    ListaString();
    bool getExpresionEsCorrecta();
    bool validarExpresion(char c);
    void agregar(char c){ cola.add(c);}
    string print();
};


class Valor : public State{
private:
    enum TipoValor { NULO, STRING, LISTA } tipo;
    Dato *valorDato;
    vector <Dato*> valores; //BUFFER
    Pila<char> p1;  
public:
    Valor()  { valorDato = nullptr;}
    bool validarExpresion(char c);
    string print();
};

#endif 
