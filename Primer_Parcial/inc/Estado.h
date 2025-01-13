#include "Pila.h"
#include "ComponenteJson.h"
#include "Cola.h"

class ExpresionJson; 

#ifndef ESTADO_H
#define ESTADO_H

class Estado{
    protected:
       ExpresionJson* expresionJson;
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
    string expresion; //buffer de caracteres
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
    Cola <String*> strings; //buffer de strings
    Pila<char> p;
    string llaves;
public:
    Llave(){
        str = nullptr;
    }
    ~Llave() {
        delete str;
    }
    bool validarExpresion(char c);
    string print();
};

//-------------------------------------------------------------------------------

class Valor : public Estado{
private:
    ComponenteJson *componenteJson;
    Cola <ComponenteJson*> valores; //buffer de valores
    Pila<char> p1;  
    string caracterIncorrecto = "";
public:
    Valor()  { componenteJson = nullptr;}
    ~Valor() { delete componenteJson; }
    bool validarExpresion(char c);
    bool validarValor(){ 
        if (componenteJson == nullptr) return true;
        return componenteJson->pilaEmpty();};
    string print();
};

#endif 
