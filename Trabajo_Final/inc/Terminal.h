#ifndef TERMINAL_H
#define TERMINAL_H
#include "Cola1.h"
#include <bitset>

class Router;
struct Pagina;


struct Paquete
{
   Pagina *pagina;
   int nroPaquete  = 0;
};

class Pagina
{
public:
    int tamaño;     // el tamaño es la cantidad de paquetes que forman la pagina 
    bitset<16> destino  = 0;
    bitset<16> origen   = 0;
    int id = 0;
    
    Pagina(int tamaño) : tamaño(tamaño){}
    
    int getByteMSB(){
        return ((destino.to_ulong() >> 8) & 0xFF);
    };
    int getByteLSB(){
        return (destino.to_ulong() & 0xFF);
    };
};

class Terminal
{
private:
    int nroPagina = 0;
    Router* router;
public:
    bitset<8> ip; // nro de terminal
    Pagina* pagina = NULL;
    Terminal(Router* router, bitset<8> n): router(router), ip(n){};
    ~Terminal(){delete pagina;};
    void emitirPagina(bitset<16> destino, int tamaño);
    void recibirPagina(Paquete* arr);
    void recibirPagina(Pagina* p);
};

#endif 