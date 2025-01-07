#include <string>
#include <fstream>

#include "../inc/ListaConAbb.h"

using namespace std;

class Nodo
{
public:
   NodoAbb* hoja;
   Nodo* der;
   Nodo* izq;
   int altura;
   Nodo(){
    hoja    = NULL;
    der     = NULL;
    izq     = NULL;
    altura  = 0;
   }
};

class ArbolPosicional
{
private:
    Nodo* raiz;
    Nodo* ultimo;
    void ArbolPos(NodoAbb *lista, Nodo*& nuevo);
    void imprimir(Nodo* NodoAbb);
public:
    ArbolPosicional(){
        raiz=new Nodo;
        ultimo = raiz;  
        raiz->altura = 1;  
    };
    void CreaArbolPos(NodoAbb *lista){ ArbolPos(lista,ultimo);};
    void ImprimirHojas(){imprimir(raiz);};
    NodoAbb* posicion(int p);
    NodoAbb* recorrer(int bin, Nodo* NodoAbb);
};

NodoAbb* ArbolPosicional::recorrer(int bin, Nodo* NodoAbb)
{
    if(NodoAbb == NULL) return NULL;
    if (NodoAbb->altura == 0)
    {
        return NodoAbb->hoja;
    }
    int msb = (bin & (1 << (raiz->altura)-1)); 
    if (msb) { // Si el bit mas significativo es 1
        return recorrer(bin << 1, NodoAbb->der); // Desplaza el número a la izq y recorre por el lado derecho
    } else { // Si el bit mas significativo es 0
        return recorrer(bin << 1, NodoAbb->izq); // Desplaza el número a la izq y recorre por el lado izquierdo
    }
}

NodoAbb* ArbolPosicional :: posicion(int p){
    p = p - 1;
    return recorrer(p,raiz);
}

void ArbolPosicional ::imprimir(Nodo* NodoAbb)
{
    if(NodoAbb == NULL) return;
    if (NodoAbb->altura == 0)
    {
        cout<<NodoAbb->hoja->info->palabra<<endl;
        return;
    }
    imprimir(NodoAbb->izq);
    imprimir(NodoAbb->der);
}

void ArbolPosicional :: ArbolPos(NodoAbb *lista, Nodo*& nuevo){
    if (nuevo->izq == nullptr)
    {
        if(nuevo->altura == 1){
            nuevo->izq = new Nodo;
            nuevo->izq->altura = nuevo->altura - 1;
            nuevo->izq->hoja = lista;
            ultimo = nuevo;
            return;
        }
        else{
            nuevo->izq = new Nodo;
            nuevo->izq->altura = nuevo->altura - 1;
            ArbolPos(lista, nuevo->izq);
            return;
        }
    }
    else if (nuevo->der == nullptr)
    {
        if(nuevo->altura == 1){
            nuevo->der = new Nodo;
            nuevo->der->altura = nuevo->altura - 1;
            nuevo->der->hoja = lista;
            ultimo = nuevo;
            return;
        }
        else{
            nuevo->der = new Nodo;
            nuevo->der->altura = nuevo->altura - 1;
            ArbolPos(lista, nuevo->der);
            return;
        }
    }    
        Nodo *nuevaRaiz = new Nodo; 
        nuevaRaiz->altura = raiz->altura + 1;
        nuevaRaiz->izq = raiz;
        raiz = nuevaRaiz;    
        ArbolPos(lista,nuevaRaiz);
}
    
void add(string palabra, ArbolAVL &T,ArbolPosicional &P) {
  T.CreaArbolAVL(palabra);
  if (T.last()->info->repeticiones == 1)
  {
    P.CreaArbolPos(T.last());
  }
}

void leer_archivo(string archivo_,  ArbolAVL &T, ArbolPosicional &P){
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
    ArbolPosicional P;
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
