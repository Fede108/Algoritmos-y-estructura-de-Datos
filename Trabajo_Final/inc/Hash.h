#include <iostream>
#include <string>
#include <Cola1.h>
#include "Vector.h"
#include "Terminal.h"
#define MAX 17

using namespace std;


// Tabla hash con dispersión abierta
template <class T> class Hash {
private:
    int Max;
    Lista<T*>* *D; 
public:
    Hash() { 
        Max = MAX; 
        D = new Lista<T*>*[MAX];
        for (int i = 0; i < Max; i++)
        {
            D[i] = nullptr; 
        }
        
    }
    void add(int id, T* p);
    void imprimir();
    int fh(int id);
    Lista<T*>* get(int id);
    void borrar(int id);
    bool esta(int id);
};

template <class T> bool Hash<T>::esta(int id){
    int i = fh(id);
    return D[i]->esvacia();
}

template <class T> void Hash<T>::borrar(int id){
    int i = fh(id);
    if  ( D[i] != nullptr) {
        delete D[i];
    }
}

template <class T> Lista<T*>* Hash<T>::get(int id){
    int i = fh(id);
    return D[i];
}

template <class T> void Hash<T>::add(int id, T* p) {
    int i = fh(id);
     if (D[i] == nullptr) {
             
        D[i] = new Lista<T*>;
    }
        D[i]->addOrdenado(p); 
}

template <class T> int Hash<T>::fh(int id) {
    string s = to_string(id);
    int i,x; 
    x=0;
    for(i=0;i<s.length();i++){
                             x=x^s[i];
                             //x=x+s[i];
                             }
   return x%Max;
}

template <class T> void Hash<T>::imprimir() {
    for (int i = 0; i < Max; i++) {
        cout << "Bucket " << i << ":" << endl;
        D[i]->impre();
    }
}


