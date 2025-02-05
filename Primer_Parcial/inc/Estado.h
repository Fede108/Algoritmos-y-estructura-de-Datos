#include "Pila.h"
#include "ComponenteJson.h"
#include "Cola.h"

class ExpresionJson; 

#ifndef ESTADO_H
#define ESTADO_H

class Estado {
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
    bool validarExpresion(char c) override;
    void guardarExpresion(char c);
    string print() override;
    int size();
    bool pilaVacia() { return p.pilavacia(); }
};

//-------------------------------------------------------------------------------

class Llave : public Estado{
private:
    String *str;
    Cola <String*> bufferStrings; 
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
    Cola <ComponenteJson*> bufferComponentes; 
    Pila<char> p1;  
    string caracterIncorrecto = "";
public:
    Valor()  { componenteJson = nullptr;}
    ~Valor() { delete componenteJson; }
    bool validarExpresion(char c);
    bool pilaVacia(){ 
        if (componenteJson == nullptr) return true;
        return componenteJson->pilaEmpty();};
    string print();
};

#endif 
