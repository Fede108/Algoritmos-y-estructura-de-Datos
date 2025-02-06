#include <string>
#include <iostream>
#include <fstream>


#include "Pila.h" 
#include "Cola.h"

using namespace std;    
class ExpresionJson; 

#ifndef ComponenteJson_H
#define ComponenteJson_H

class ComponenteJson
{
public:
    virtual ~ComponenteJson() = default;
    virtual bool validarExpresion(char c)= 0;
    virtual bool  getExpresionEsCorrecta() = 0;
    virtual string print() = 0;
    virtual bool pilaEmpty() = 0;
};

//-------------------------------------------------------------------------------

class JsonAyed : public ComponenteJson       // clase vacia
{
public:
    bool validarExpresion(char c) override {
        return false; }
    bool getExpresionEsCorrecta() override {
        return true;  }
    string print() override {
        return "{}";  }
    bool pilaEmpty() override {
        return true;  }
};

//-------------------------------------------------------------------------------

class String : public ComponenteJson
{
private:
    Pila<char> p;
    bool expresionCorrecta = false;
    string str; //buffer de char
public:
    bool validarExpresion(char c);
    bool getExpresionEsCorrecta();
    string print();
    bool pilaEmpty(){return p.pilavacia();};
};

//-------------------------------------------------------------------------------

class ListaString : public ComponenteJson
{
private:
    bool expresionCorrecta = false;
    Pila<char> p;
    Cola<char> cola;                    // cola para almacenar los valores de la lista de strings
    Cola <String*> bufferStrings;
    String *str;  
    string cadena;
public:
    ListaString(){ str = nullptr;}
    ~ListaString() { delete str; }
    bool getExpresionEsCorrecta();
    bool validarExpresion(char c);
    void agregar(char c){ cola.add(c);}
    string print();
    bool pilaEmpty( ){return p.pilavacia();};
};

#endif 
