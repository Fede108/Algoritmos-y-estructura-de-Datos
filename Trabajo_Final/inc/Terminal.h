#ifndef TERMINAL_H
#define TERMINAL_H
#include "Router.h"

struct Pagina
{
    int ip = 0;
    int tamaño = 0;
    int informacion = 0;
};

class Terminal
{
private:
    Router* router;
    Pagina* pagina;
public:
    Terminal(Router* router);
    ~Terminal();
    void enviarPagina();
};

struct Paquete
{
   int ip = 0;
   int nroPaquete = 0;
   int informacion = 0;
};


#endif 