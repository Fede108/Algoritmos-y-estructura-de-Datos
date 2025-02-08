#include <iostream>


using namespace std;

#include <iostream>
#include <string>
#include "Cola.h"
#include "Vector.h"
#include "Terminal.h"
#define MAX 17


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
    Lista<HashEntry<T>*> *D; 
public:
    Hash() { 
        Max = MAX; 
        D = new Lista<HashEntry<T>*>[MAX];     
    }
    bool add(int id, T p);
    int fh(int id);
    T get (int id);
    void borrar(int id);
    bool esta(int id);
    Vector<T> listar(); 
    void imprimir();
};

template <class T> bool Hash<T>::esta(int id){
    int i = fh(id);
    if  ( !D[i].esvacia()) {    // si la lista esta vacia no hay ningun hashEntry con esa key
        Lista<HashEntry<T>*> *aux = new Lista<HashEntry<T>*>;
        aux = D[i].copy();
        while (!aux->esvacia())
        {
            if(aux->cabeza()->key == id){
                return true;
            }  
            aux->borrar();  
        }
        return false; 
    }
    return false;
}

template <class T> void Hash<T>::borrar(int id) {
    int i = fh(id);
    if  ( !D[i].esvacia()) {
        Lista<HashEntry<T>*> *aux = new Lista<HashEntry<T>*>;
        aux = D[i].copy();
         while (!aux->esvacia())      // recorro la lista buscando la hashEntry
        {
            if(aux->cabeza()->key == id){        // si la key coincide con el id
                HashEntry<T>* entry = aux->cabeza();
                this->D[i].borrarDato(entry);  // se borra el dato de la lista
                delete entry;       // se borra el dato
                break;  
            }  
            aux->borrar();       // se itera sobre la lista borrando la cabeza
        } 
    }
} 

template <class T> T Hash<T>::get(int id){
    int i = fh(id);
    if (D[i].esvacia()) return T();
    Lista<HashEntry<T>*> *aux = new Lista<HashEntry<T>*>;
    aux = D[i].copy();
    while (!aux->esvacia())
    {
        if(aux->cabeza()->key == id) return aux->cabeza()->value;
        aux->borrar();
    } 

}

template <class T> bool Hash<T>::add(int id, T p) {
    int i = fh(id);
      // recorro la lista buscando elemento 
    if(! esta(id) ){
        D[i].add( new HashEntry(id, p));  // si no esta se agrega 
        return true;
    } 
    else{
        return false;  // si ya se encuentra no lo agrego
    } 
}

template <class T> Vector<T> Hash<T>::listar() {
    Vector<T> resultado;  
    // recorro cada posicion del arreglo de listas
    for (int i = 0; i < Max; i++) {
        if (!D[i].esvacia()) {  // si existe una lista en esta posicion
            Lista<HashEntry<T>*> *aux = new Lista<HashEntry<T>*>;
            aux = D[i].copy();
            while (!aux->esvacia()) {
                resultado.push(aux->cabeza()->value); // agrego el valor de la entrada al vector
                aux->borrar();
            }
        }
    }
    return resultado;
}


template <class T>
void Hash<T>::imprimir() {
    for (int i = 0; i < Max; i++) {
        cout << "Bucket " << i << ": ";
        if (D[i].esvacia()) {
            cout << "vacio" << endl;
        } else {
            D[i].toPrint("");
        }
    }
}

template <class T>
int Hash<T>::fh(int id) {
    return id % Max;
}


int main() {
    // Crear una tabla hash
    Hash<string> hash;

    // Agregar elementos que colisionan (por ejemplo, id % 17 == 0)
    hash.add(0, "Valor0");
    hash.add(17, "Valor17");
    hash.add(34, "Valor34");
    hash.add(51, "Valor51");

    // Imprimir el estado inicial del hash
    cout << "Estado inicial del hash:" << endl;
   // hash.imprimir();

    // Verificar búsqueda de valores
    cout << "Buscando valores:" << endl;
    cout << "Clave 0: " << hash.get(0) << endl;
    cout << "Clave 17: " << hash.get(17) << endl;
    cout << "Clave 34: " << hash.get(34) << endl;
    cout << "Clave 51: " << hash.get(51) << endl;

    // Eliminar valores
    cout << "Eliminando claves..." << endl;
    hash.borrar(17);
    hash.borrar(34);
    hash.borrar(0);
    hash.borrar(51);

    // Imprimir el estado del hash después del borrado
    cout << "Estado del hash después de eliminar claves:" << endl;
 //   hash.imprimir();

    // Intentar buscar valores eliminados
    cout << "Buscando valores después del borrado:" << endl;
    cout << "Clave 17: " << hash.get(17) << endl; // Debería devolver vacío o un valor predeterminado
    cout << "Clave 34: " << hash.get(34) << endl; // Debería devolver vacío o un valor predeterminado

    return 0;
}
