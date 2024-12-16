//  Pila con Arreglo.cpp  
//

#include <cstdlib>
#include <iostream>
#include <sstream>

#ifndef PILA_H
#define PILA_H


#define MAX 100
using namespace std;

// Pila arreglo con estructura estatica

template <class T> class Pila {
private:
    T d[MAX];
    int p;
public:
    Pila() { p = -1; };
    void apilar(T x) { d[++p] = x; };
    T tope(void) { return d[p]; };
    void desapilar(void) { p--; };
    bool pilavacia() { return p == -1; };
};

#endif
