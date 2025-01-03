#include <string>
#include <iostream>
#include <fstream>
#include <vector>


#include "Pila.h" 
#include "Cola.h"

using namespace std;    
class ExpresionJson; 

#ifndef DATO_H
#define DATO_H

class Dato
{
public:
    virtual bool validarExpresion(char c)= 0;
    virtual bool  getExpresionEsCorrecta() = 0;
    virtual string print() = 0;
    virtual bool pilaEmpty() = 0;
};

//-------------------------------------------------------------------------------

class JsonAyed : public Dato
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

class String : public Dato
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

class ListaString : public Dato
{
private:
    bool expresionCorrecta = false;
    Pila<char> p;
    Cola<char> cola;
    vector <String*> strings; //BUFFER
    String *str;  
    string cadena;
public:
    ListaString(){ str = nullptr;}
    bool getExpresionEsCorrecta();
    bool validarExpresion(char c);
    void agregar(char c){ cola.add(c);}
    string print();
    bool pilaEmpty( ){return p.pilavacia();};
};

#endif 
