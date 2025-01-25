#include <iostream>


using namespace std;

#include <iostream>
#include <string>
#include "Cola1.h"
#include "Vector.h"
#include "Terminal.h"
#define MAX 17

using namespace std;

template <class T> class HashEntry
{
    public:
        int key;
        T value;
        HashEntry(int key, T value)
        {
            this->key = key;
            this->value = value;
        }
};

// Tabla hash con dispersión abierta
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
    void add(int id, T p);
    void imprimir();
    int fh(int id);
    T get(int id);
    void borrar(int id);
    bool esta(int id);
};

template <class T> void Hash<T>::borrar(int id) {
    int i = fh(id);
    if  ( D[i] != nullptr) {
         Lista<HashEntry<T>*>* aux = D[i];
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

template <class T> void Hash<T>::add(int id, T p) {
    int i = fh(id);
     if (D[i] == nullptr) {
         D[i] = new Lista<HashEntry<T>*>;
    }
        D[i]->add( new HashEntry(id, p)); 
}

template <class T>
int Hash<T>::fh(int id) {
    return id % Max;
}

template <class T>
void Hash<T>::imprimir() {
    for (int i = 0; i < Max; i++) {
        cout << "Bucket " << i << ": ";
        if (D[i] == nullptr || D[i]->esvacia()) {
            cout << "vacio" << endl;
        } else {
            D[i]->toPrint("");
        }
    }
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
    hash.imprimir();

    // Intentar buscar valores eliminados
    cout << "Buscando valores después del borrado:" << endl;
    cout << "Clave 17: " << hash.get(17) << endl; // Debería devolver vacío o un valor predeterminado
    cout << "Clave 34: " << hash.get(34) << endl; // Debería devolver vacío o un valor predeterminado

    return 0;
}
