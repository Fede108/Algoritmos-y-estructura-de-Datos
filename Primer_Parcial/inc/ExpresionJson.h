#include "Estado.h"
#include <string>
using namespace std;    

#ifndef EXPRESIONJSON_H
#define EXPRESIONJSON_H

class ExpresionJson
{
private:
    Estado* estadoActual;
    EntreLlaves entreLlaves; // Instancia única
    Llave llave;                 // Instancia única
    Valor valor;                 // Instancia única
    string json;
public:
    ExpresionJson() {
        estadoActual = &entreLlaves; // Estado inicial
        estadoActual->setExpresionJson(this);
    }
    void setEstado(Estado* estado);
    bool leer_archivo(string nombre_archivo);
    void generar_archivo();
    // string imprimir_archivo();
    Estado* getEntreLlaves() { return &entreLlaves; };
    Estado* getLlave() { return &llave; };
    Estado* getValor() { return &valor; };
   
};

#endif 



     
