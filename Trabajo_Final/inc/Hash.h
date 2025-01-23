#include <iostream>
#include <string>
#include <Cola1.h>
#include "Vector.h"
#include "Terminal.h"
#define MAX 17

using namespace std;


// Tabla hash con dispersión abierta
class Hash {
private:
    int Max;
    Lista<Paquete*> *D; 
public:
    Hash() { 
        Max = MAX; 
        D = new Lista<Paquete*>[MAX];
    }
    void add(int id, Paquete* p);
    void imprimir();
    int fh(int id);
    Lista<Paquete*> get(int id);
    void borrar(int id);
    bool esta(int id);
};

bool Hash::esta(int id){
    int i = fh(id);
    return D[i].esvacia();
}

void Hash::borrar(int id){
    int i = fh(id);
    delete &D[i];
}

Lista<Paquete*> Hash::get(int id){
    int i = fh(id);
    return D[i];
}

void Hash::add(int id, Paquete* p) {
    int i = fh(id);
    D[i].addOrdenado(p);
}

int Hash::fh(int id) {
    string s = to_string(id);
    int i,x; 
    x=0;
    for(i=0;i<s.length();i++){
                             x=x^s[i];
                             //x=x+s[i];
                             }
   return x%Max;
}

void Hash::imprimir() {
    for (int i = 0; i < Max; i++) {
        cout << "Bucket " << i << ":" << endl;
        D[i].impre();
    }
}


