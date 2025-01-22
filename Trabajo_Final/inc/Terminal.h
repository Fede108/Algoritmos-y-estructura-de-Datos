#ifndef TERMINAL_H
#define TERMINAL_H
#include "Cola.h"
#include <bitset>

class Router;

struct Pagina
{
    bitset<8> ip = 0;
    int tamaño = 0;
    int informacion = 0;
};

struct Paquete
{
   bitset<8> ip = 0;
   int nroPaquete = 0;
   int informacion = 0;
};

class Terminal
{
private:
    Router* router;
    Pagina* pagina;
    Lista<Paquete*> paquetes;
    bitset<4> n; // nro de terminal
public:
    Terminal(Router* router, bitset<4> n);
    ~Terminal();
    void enviarPagina(int x);
    void recibirPagina(Paquete* p);
};


#endif 