#include "State.h"
#include <string>
using namespace std;    
#ifndef CONTEXT_H
#define CONTEXT_H
class Context
{
private:
   State* estadoActual;
public:
    Context();
    void setEstado(State* estado);
    void leer_archivo(string nombre_archivo);

};
#endif 



     
