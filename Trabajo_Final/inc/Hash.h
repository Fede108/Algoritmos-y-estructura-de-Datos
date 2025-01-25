
#include <iostream>
#include <string>
#include "Cola1.h"
#include "Vector.h"
#include "Terminal.h"
#define MAX 17

using namespace std;

template <class K, class V> class HashEntry {
public:
    K key; 
    V value; 
    HashEntry(K key, V value) {
        this->key = key;
        this->value = value;
    }
};

template <class K, class V> class Hash {
private:
    int Max;
    Lista<HashEntry<K, V>*> **D; 
public:
    Hash() { 
        Max = MAX; 
        D = new Lista<HashEntry<K, V>*>*[MAX];
        for (int i = 0; i < Max; i++)
        {
            D[i] = nullptr; 
        }
        
    }
    void add(K id, V p);
    int fh(K id);
    V get(K id);
    void borrar(K id);
};

template <class K, class V> void Hash<K, V>::borrar(K id) {
    int i = fh(id);
    if  ( D[i] != nullptr) {
         Lista<HashEntry<K, V>*>* aux = D[i];
         while (!aux->esvacia())
        {
            if(aux->cabeza()->key == id){
                this->D[i]->borrarDato(aux->cabeza());
                break;  // borra la cabeza
            }  
            aux = aux->resto();
        } 
        if(this->D[i]->esvacia()){
            delete this->D[i];
            this->D[i]=nullptr;
        }  
    }
} 

template <class K, class V> V Hash<K, V>::get(K id){
    int i = fh(id);
    if (D[i] == nullptr) return 0;
    Lista<HashEntry<K, V>*>* aux = D[i];
    while (!aux->esvacia())
    {
        if(aux->cabeza()->key == id) return aux->cabeza()->value;
        aux = aux->resto();
    } 

    return  0;
}

template <class K, class V> void Hash<K, V>::add(K id, V p) {
    int i = fh(id);
     if (D[i] == nullptr) {
         D[i] = new Lista<HashEntry<K, V>*>;
    }
        D[i]->add( new HashEntry<K, V>(id, p)); 
}

template <class K, class V>
int Hash<K, V>::fh(K id) {
    return id.to_ulong() % Max;
}


