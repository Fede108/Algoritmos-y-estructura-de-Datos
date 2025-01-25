#ifndef TERMINAL_H
#define TERMINAL_H
#include "Cola1.h"
#include <bitset>

class Router;

class Pagina
{
public:
    bitset<16> destino = 0;
    bitset<8> origen = 0;
    int tamaño = 0;         // el tamaño es la cantidad de paquetes que forman la pagina  
    int informacion = 0;
    int id = 0;
    bitset<8> getByteMSB(){
         bitset<8> ByteMSB((destino.to_ulong() >> 8) & 0xFF);
         return ByteMSB;
    };
    bitset<8> getByteLSB(){
         bitset<8> ByteLSB(destino.to_ulong() & 0xFF);
         return ByteLSB;
    };
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
    int nroPagina = 0;
    Router* router;
    Lista<Paquete*> paquetes;
public:
    int nroPaquete;
    bitset<8> ip; // nro de terminal
    Pagina* pagina = NULL;
    Terminal(Router* router, bitset<8> n);
    ~Terminal();
    void enviarPagina(int destino, int tamaño);
    void recibirPagina(Pagina* p);
};


#endif 