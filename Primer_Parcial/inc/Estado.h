#include "Pila.h"
#include "Dato.h"
#include <vector> 
class ExpresionJson; 

#ifndef ESTADO_H
#define ESTADO_H

class Estado{
    protected:
       ExpresionJson* expresionJson;
       string expresion;
    public:
        virtual ~Estado() = default;
        void setExpresionJson(ExpresionJson* ctx) {
            expresionJson = ctx;
        }   
        ExpresionJson* getExpresionJson(){return expresionJson;}
        virtual bool validarExpresion(char c) = 0;
        virtual string print() = 0;
}; 

//-------------------------------------------------------------------------------

class EntreLlaves : public Estado {
private:
    string expresion;
    Pila<char> p;
public:
    // Métodos de ExpresionJson
    bool validarExpresion(char c) override;
    void guardarExpresion(char c);
    string print() override;
    int size();
    bool validarJson() { return p.pilavacia(); }
};

//-------------------------------------------------------------------------------

class Llave : public Estado{
private:
    String *str;
    vector <String> strings; //buffer de strings
    Pila<char> p;
    string llaves;
public:
    Llave(){
        str = new String();
    }
    ~Llave() {
        delete str;
    }
    bool validarExpresion(char c);
    string print();
    bool validarLlave( ){ 
        return !p.pilavacia() && str->pilaEmpty();
    };
};

//-------------------------------------------------------------------------------

class Valor : public Estado{
private:
    Dato *valorDato;
    vector <Dato*> valores; //BUFFER
    Pila<char> p1;  
public:
    Valor()  { valorDato = nullptr;}
    bool validarExpresion(char c);
    bool validarValor(){ 
        if (valorDato == nullptr) return true;
        return valorDato->pilaEmpty();};
    string print();
};

#endif 
