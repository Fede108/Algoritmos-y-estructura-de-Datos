#include <string>
#include <fstream>

#include "../inc/ListaConAbb.h"
#include <queue>
#include <stack>

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
    stack<Nodo*> pila;
    void ArbolPos(NodoAbb *lista, Nodo*& nuevo);
    void imprimir(Nodo* NodoAbb);
public:
    ArbolPosicional(){
        raiz=new Nodo;
        ultimo = raiz;  
        raiz->altura = 1;
        pila.push(raiz);  
    };
    void CreaArbolPos(NodoAbb *lista){ ArbolPos(lista,pila.top());};
    void ImprimirHojas(){imprimir(raiz);};
    NodoAbb* posicion(int p);
    NodoAbb* recorrer(int bin, Nodo* NodoAbb);
};

NodoAbb* ArbolPosicional::recorrer(int bin, Nodo* NodoAbb)
{
    while (NodoAbb->altura > 0)
    {
        int msb = (bin >> (NodoAbb->altura - 1)) & 1;
        if (msb) { // Si el bit mas significativo es 1
            NodoAbb = NodoAbb->der; // recorre por el lado derecho 
        } else { // Si el bit mas significativo es 0
            NodoAbb = NodoAbb->izq; // recorre por el lado izquierdo
        }
        if(NodoAbb == NULL) return NULL;
    }
    return NodoAbb->hoja;
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
            return;
        }
        else{   
            nuevo->izq = new Nodo;
            nuevo->izq->altura = nuevo->altura - 1;
            pila.push(nuevo->izq);
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
            return;
        }
        else{
            nuevo->der = new Nodo;
            nuevo->der->altura = nuevo->altura - 1;
            pila.push(nuevo->der);
            ArbolPos(lista, nuevo->der);
            return;
        }
    }    

    pila.pop();
    if (!pila.empty())
    {
        ArbolPos(lista, pila.top());
        return;
    }
    Nodo *nuevaRaiz = new Nodo; 
    nuevaRaiz->altura = raiz->altura + 1;
    nuevaRaiz->izq = raiz;
    raiz = nuevaRaiz;    
    ArbolPos(lista,nuevaRaiz);
}

void ordenaSeleccion(ArbolPosicional &P,int N){
    int i,j,pos,m=0,c=0;
    Dato* men;
    for(i=1;i<N;i++){

        men = P.posicion(i)->info; pos=i; m++;  // n-1 movimientos

        for(j=i+1;j<N;j++){  // n-1 veces
            c++; // n-i-1 comparaciones 
            if( P.posicion(j)->info->repeticiones < men->repeticiones ){ 
                men = P.posicion(j)->info; m++; // aprox n/2 veces por iteracion en el peor caso, max a min 
                pos = j;
            }
        }

        P.posicion(pos)->info = P.posicion(i)->info; m++; // 2*(n-1) movimientos
        P.posicion(i)->info = men; m++;

    }
}
    
int add(string palabra, ArbolAVL &T,ArbolPosicional &P) {
  int N = 0;
  T.CreaArbolAVL(palabra);
  if (T.last()->info->repeticiones == 1)
  {
    P.CreaArbolPos(T.last());
    N++;
  }
  return N;
}

int leer_archivo(string archivo_,  ArbolAVL &T, ArbolPosicional &P){
    int N = 0;
    string palabra;
    ifstream archivo(archivo_);
    if (archivo.is_open() ){
        char c;
        while(archivo.get(c)){
            if (isalnum(c)){
              palabra += c;  
            } else if (!palabra.empty())
            {    
                N += add(palabra, T, P);
                palabra = ""; 
            }   
        }
        archivo.close();
    }
    return N;
}

int main(){
    ArbolAVL T;
    ArbolAVL *T_copy;
    ArbolPosicional P;
    int N = leer_archivo("data.txt", T, P);
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
    ordenaSeleccion(P,N);
    P.ImprimirHojas();
    cout<<endl;system("PAUSE");
}
