
#include <iostream>
#include <string>
#include "Cola1.h"
#include "Vector.h"
#include "Terminal.h"
#define MAX 17

using namespace std;

template <class V> class HashEntry {
public:
    int key; 
    V value; 
    HashEntry(int key, V value) {
        this->key = key;
        this->value = value;
    }
};

template <class T> class Hash {
private:
    int Max;
    Lista<HashEntry<T>*> **D; 
public:
    Hash() { 
        Max = MAX; 
        D = new Lista<HashEntry<T>*>*[MAX];
        for (int i = 0; i < Max; i++)
        {
            D[i] = nullptr; 
        }
        
    }
    bool add(int id, T p);
    int fh(int id);
    T get (int id);
    void borrar(int id);
    bool esta(int id);
    Vector<T> listar(); 
};

template <class T> bool Hash<T>::esta(int id){
    int i = fh(id);
    if  ( D[i] != nullptr) {
        Lista<HashEntry<T>*>* aux = D[i];
        while (!aux->esvacia())
        {
            if(aux->cabeza()->key == id){
                return true;
            }  
            aux = aux->resto();
        }
        return false; 
    }
    return false;
}

template <class T> void Hash<T>::borrar(int id) {
    int i = fh(id);
    if  ( D[i] != nullptr) {
         Lista<HashEntry<T>*>* aux = D[i];
         while (!aux->esvacia())      // recorro la lista buscando la hashEntry
        {
            if(aux->cabeza()->key == id){        // si la key coincide con el id
                HashEntry<T>* entry = aux->cabeza();
                this->D[i]->borrarDato(entry);  // se borra el dato de la lista
                delete entry;       // se borra el dato
                break;  
            }  
            aux = aux->resto();
        } 
        if(this->D[i]->esvacia()){
            delete this->D[i];
            this->D[i]=nullptr;
        }  
    }
} 

template <class T> T Hash<T>::get(int id){
    int i = fh(id);
    if (D[i] == nullptr) return 0;
    Lista<HashEntry<T>*>* aux = D[i];
    while (!aux->esvacia())
    {
        if(aux->cabeza()->key == id) return aux->cabeza()->value;
        aux = aux->resto();
    } 

    return  0;
}

template <class T> bool Hash<T>::add(int id, T p) {
    int i = fh(id);
    if (D[i] == nullptr) {
        D[i] = new Lista<HashEntry<T>*>;
        D[i]->add( new HashEntry(id, p));
        return true;
    } 
    else  // recorro la lista buscando elemento 
    {
        if(! esta(id) ){
            D[i]->add( new HashEntry(id, p));
            return true;
        } 
        else{
            return false;  // si ya se encuentra no lo agrego
        } 
         
    }
         
}

template <class T> Vector<T> Hash<T>::listar() {
    Vector<T> resultado;  
    // recorro cada posicion del arreglo de listas
    for (int i = 0; i < Max; i++) {
        if (D[i] != nullptr) {  // si existe una lista en esta posicion
            Lista<HashEntry<T>*>* aux = D[i];
            while (!aux->esvacia()) {
                resultado.push(aux->cabeza()->value); // agrego el valor de la entrada al vector
                aux = aux->resto();
            }
        }
    }
    return resultado;
}

template <class T>
int Hash<T>::fh(int id) {
    return id % Max;
}


