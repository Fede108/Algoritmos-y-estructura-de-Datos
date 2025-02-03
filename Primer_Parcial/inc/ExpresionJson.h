#include "Estado.h"
#include <string>
using namespace std;    

#ifndef EXPRESIONJSON_H
#define EXPRESIONJSON_H

class ExpresionJson
{
private:
    Estado* estadoActual;
    EntreLlaves entreLlaves;    
    Llave llave;                
    Valor valor;                
    string json;
    int caracter;
    bool correcto;
public:
    ExpresionJson() {
        estadoActual = &entreLlaves; // estado inicial
        estadoActual->setExpresionJson(this);
        caracter = 0;
    }
    void setEstado(Estado* estado);
    bool leer_archivo(string nombre_archivo);
    void generar_archivo();
   
    Estado* getEntreLlaves() { return &entreLlaves; };
    Estado* getLlave() { return &llave; };
    Estado* getValor() { return &valor; };
   
};

#endif 



     
