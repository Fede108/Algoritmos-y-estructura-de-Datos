#ifndef TERMINAL_H
#define TERMINAL_H
#include "Cola1.h"
#include <bitset>

class Router;

struct Pagina
{
    bitset<8> ip = 0;
    int tamaño = 0;
    int informacion = 0;
    int id = 0;
};

struct Paquete
{
   Pagina *pagina;
   int nroPaquete  = 0;
   int informacion = 0;
};

class Terminal
{
private:
    Router* router;
    Lista<Paquete*> paquetes;
public:
    bitset<4> n; // nro de terminal
    Pagina* pagina = NULL;
    Terminal(Router* router, bitset<4> n);
    ~Terminal();
    void enviarPagina(int x);
    void recibirPagina(Pagina* p);
};


#endif 