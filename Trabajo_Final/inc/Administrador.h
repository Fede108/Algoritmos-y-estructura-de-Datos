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
    void crearGrafo(int n, int N, int a, int t);
    void simular();
    void generarDOT();
};

#endif