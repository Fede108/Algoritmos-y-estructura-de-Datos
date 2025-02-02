#ifndef TERMINAL_H
#define TERMINAL_H
#include "Cola.h"
#include <bitset>
#include <cstdint>

class Router;
struct Pagina;

struct Paquete
{
    Pagina *pagina;
    int nroPaquete  = 0;
    friend bool operator<(Paquete p1, Paquete p2) {
        return p1.nroPaquete < p2.nroPaquete;
    }
};

class Pagina
{
public:
    int tamaño;     // el tamaño es la cantidad de paquetes que forman la pagina 
    Paquete* paquetes; 
    bitset<16> destino  = 0;
    bitset<16> origen   = 0;
    int id = 0;
    
    Pagina(int tamaño) : tamaño(tamaño){ 
        paquetes = NULL;
    }
    ~Pagina(){ delete paquetes;}
    int getTermDestino(){
        return ((destino.to_ulong() >> 8) & 0xFF);
    };
    int getRoutDestino(){
        return (destino.to_ulong() & 0xFF);
    };
    int getTermOrigen(){
        return ((origen.to_ulong() >> 8) & 0xFF);
    };
    int getRoutOrigen(){
        return (origen.to_ulong() & 0xFF);
    };

};

class Terminal
{
private:
    int nroPagina = 0;
    Router* router;
public:
    int ip; // nro de terminal
    Pagina* pagina = nullptr;
    Terminal(Router* router, int n): router(router), ip(n){};
    ~Terminal(){delete pagina;};
    void emitirPagina(bitset<16> destino, int tamaño);
    void recibirPagina(Pagina* p);
};

#endif 