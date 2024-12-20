#include "State.h"
#include "Llave.h"
#include "Valor.h"
#include "ExpresionJson.h"
#include <string>
using namespace std;    
#ifndef CONTEXT_H
#define CONTEXT_H
class Context
{
private:
    State* estadoActual;
    ExpresionJson expresionJson; // Instancia única
    Llave llave;                 // Instancia única
    Valor valor;                 // Instancia única
public:
    Context() : expresionJson(this), llave(this), valor(this) {
        estadoActual = &expresionJson; // Estado inicial
    }
    void setEstado(State* estado);
    void leer_archivo(string nombre_archivo);
    State* getExpresionJson() { return &expresionJson; };
    State* getLlave() { return &llave; };
    State* getValor() { return &valor; };
};
#endif 



     
