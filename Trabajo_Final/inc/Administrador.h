#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H
#include <iostream>
using namespace std;
#include "Router.h"
#include "Grafo.h"
#include <vector>


class Administrador
{
private:
    Grafo *grafo;
public:
    void crearRed(string archivo);
    void simular();
    void crearNuevaPagina();
    void generarDOT();
};

#endif