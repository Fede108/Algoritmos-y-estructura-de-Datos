#ifndef TERMINAL_H
#define TERMINAL_H
#include "Cola.h"
class Router;

struct Pagina
{
    int ip = 0;
    int tamaño = 0;
    int informacion = 0;
};

struct Paquete
{
   int ip = 0;
   int nroPaquete = 0;
   int informacion = 0;
};

class Terminal
{
private:
    Router* router;
    Pagina* pagina;
    Lista<Paquete*> paquetes;
public:
    Terminal(Router* router);
    ~Terminal();
    void enviarPagina(int x);
    void recibirPagina(Paquete* p);
};




#endif 