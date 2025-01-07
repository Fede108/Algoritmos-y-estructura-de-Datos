#include <string>
#include <fstream>

#include "../inc/ListaConAbb.h"

using namespace std;

class NodoAb
{
public:
   Nodo* hoja;
   NodoAb* der;
   NodoAb* izq;
   int altura;
   NodoAb(){
    hoja    = NULL;
    der     = NULL;
    izq     = NULL;
    altura  = 0;
   }
};

class ArbolBinario
{
private:
    NodoAb* raiz;
    NodoAb* ultimo;
    void ArbolPos(Nodo *lista, NodoAb*& nuevo);
    void imprimir(NodoAb* nodo);
public:
    ArbolBinario(){
        raiz=new NodoAb;
        ultimo = raiz;  
        raiz->altura = 1;  
    };
    void CreaArbolPos(Nodo *lista){ ArbolPos(lista,ultimo);};
    void ImprimirHojas(){imprimir(raiz);};
    Nodo* posicion(int p);
    Nodo* recorrer(int bin, NodoAb* nodo);
};

Nodo* ArbolBinario::recorrer(int bin, NodoAb* nodo)
{
    if(nodo == NULL) return;
    if (nodo->altura == 0)
    {
        return nodo->hoja;
    }
    int msb = (bin & (1 << (raiz->altura)-1)); 
    if (msb) { // Si el bit mas significativo es 1
        return recorrer(bin << 1, nodo->der); // Desplaza el número a la izq y recorre por el lado derecho
    } else { // Si el bit mas significativo es 0
        return recorrer(bin << 1, nodo->izq); // Desplaza el número a la izq y recorre por el lado izquierdo
    }
}

Nodo* ArbolBinario :: posicion(int p){
    p = p - 1;
    return recorrer(p,raiz);
}

void ArbolBinario ::imprimir(NodoAb* nodo)
{
    if(nodo == NULL) return;
    if (nodo->altura == 0)
    {
        cout<<nodo->hoja->info->palabra<<endl;
        return;
    }
    imprimir(nodo->izq);
    imprimir(nodo->der);
}

void ArbolBinario :: ArbolPos(Nodo *lista, NodoAb*& nuevo){
    if (nuevo->izq == nullptr)
    {
        if(nuevo->altura == 1){
            nuevo->izq = new NodoAb;
            nuevo->izq->altura = nuevo->altura - 1;
            nuevo->izq->hoja = lista;
            ultimo = nuevo;
            return;
        }
        else{
            nuevo->izq = new NodoAb;
            nuevo->izq->altura = nuevo->altura - 1;
            ArbolPos(lista, nuevo->izq);
            return;
        }
    }
    else if (nuevo->der == nullptr)
    {
        if(nuevo->altura == 1){
            nuevo->der = new NodoAb;
            nuevo->der->altura = nuevo->altura - 1;
            nuevo->der->hoja = lista;
            ultimo = nuevo;
            return;
        }
        else{
            nuevo->der = new NodoAb;
            nuevo->der->altura = nuevo->altura - 1;
            ArbolPos(lista, nuevo->der);
            return;
        }
    }    
        NodoAb *nuevaRaiz = new NodoAb; 
        nuevaRaiz->altura = raiz->altura + 1;
        nuevaRaiz->izq = raiz;
        raiz = nuevaRaiz;    
        ArbolPos(lista,nuevaRaiz);
}
    
void add(string palabra, ArbolAVL &T,ArbolBinario &P) {
  T.CreaArbolAVL(palabra);
  if (T.last()->info->repeticiones == 1)
  {
    P.CreaArbolPos(T.last());
  }
}

void leer_archivo(string archivo_,  ArbolAVL &T, ArbolBinario &P){
    string palabra;
    ifstream archivo(archivo_);
    if (archivo.is_open() ){
        char c;
        while(archivo.get(c)){
            if (isalnum(c)){
              palabra += c;  
            } else if (!palabra.empty())
            {    
                add(palabra, T, P);
                palabra = ""; 
            }   
        }
        archivo.close();
    }
}

int main(){
    ArbolAVL T;
    ArbolAVL *T_copy;
    ArbolBinario P;
    leer_archivo("data.txt", T, P);
    T_copy = T.Copy();
    T.VerArbol();
    T.IRD();
    cout << "\n";
    T.print();
//    T_copy->VerArbol();
//    T_copy->IRD();
    cout << "\n";
    P.ImprimirHojas();
    cout << "\n"<< P.posicion(3)->info->palabra<<endl;
    cout<<endl;system("PAUSE");
}
