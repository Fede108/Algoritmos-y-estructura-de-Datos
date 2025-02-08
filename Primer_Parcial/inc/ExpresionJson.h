#include "Estado.h"
#include <string>
using namespace std;    

#ifndef EXPRESIONJSON_H
#define EXPRESIONJSON_H

class ExpresionJson
{
private:
    Estado* estadoActual;  // puede apuntar a cualquier tipo de estado 
    EntreLlaves entreLlaves;    
    Llave llave;                
    Valor valor;                
    string json;
    int caracter;
    bool correcto;
public:
    ExpresionJson() {
        // cada tipo de expresion tiene un puntero a la expresion jsonAyed
        entreLlaves.setExpresionJson(this);
        llave.setExpresionJson(this);
        valor.setExpresionJson(this);
      
        estadoActual = &entreLlaves; // estado inicial
        caracter = 0;
    }
    void setEstado(Estado* estado);   // seteo el estado segun el modo siguiente correspondiente
    bool leer_archivo(string nombre_archivo); 
    void generar_archivo();
   
    Estado* getEntreLlaves() { return &entreLlaves; };
    Estado* getLlave() { return &llave; };
    Estado* getValor() { return &valor; };
   
};

#endif 



     
