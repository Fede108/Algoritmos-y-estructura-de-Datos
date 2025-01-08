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
        nuevo->izq = new Nodo;
        nuevo->izq->altura = nuevo->altura - 1;

        if(nuevo->altura == 1){
            nuevo->izq->hoja = lista;
            return;
        }
        else{   
            pila.push(nuevo->izq);
            ArbolPos(lista, nuevo->izq);
            return;
        }
    }
    else if (nuevo->der == nullptr)
    {
        nuevo->der = new Nodo;
        nuevo->der->altura = nuevo->altura - 1;

        if(nuevo->altura == 1){
            nuevo->der->hoja = lista;
            return;
        }
        else{
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

//--------------------------------------------------------------------------------------


void ordenaSeleccion(ArbolPosicional &P,int N);
int mapear(ArbolPosicional &P, ArbolAVL *T);
void leer_archivo(string archivo_,  ArbolAVL &T);

int main(){
    ArbolAVL T;
    ArbolAVL *T_copy;
    ArbolPosicional P;
    leer_archivo("data.txt", T);
    T_copy = T.Copy();
    T.VerArbol();
    T.IRD();
    cout << "\n";
//    T.print();
    T_copy->VerArbol();
    T_copy->IRD();
    cout << "\n";
    cout << "\n";
    cout << "\n";
    int N = mapear(P, &T);
 //   P.ImprimirHojas();
    ordenaSeleccion(P,N);
    cout << "\n";
    cout << "\n";
//    P.ImprimirHojas();
    cout << "\n";
    cout << "\n";
//    T.print();
    cout<<endl;system("PAUSE");
}

void ordenaSeleccion(ArbolPosicional &P,int N){
    int i,j,pos,m=0,c=0;
    Dato* max;
    for(i=1;i<N;i++){ // recorro desde pos 1 a N-1

        max = P.posicion(i)->info; // supone el max como primer posicion subconjunto [i:N]
        pos=i; m++;  // n-1 movimientos

        for(j=i+1;j<=N;j++){  // recorre el subconjunto [i+1:N] n-1 veces
            c++; // n-i-1 comparaciones 
            if( P.posicion(j)->info->repeticiones > max->repeticiones ){ // si encuentra un elemento con mas repeticiones
                max = P.posicion(j)->info; // actualiza el max del subconjunto
                m++; // aprox n/2 veces por iteracion en el peor caso, max a min 
                pos = j; // guarda posicion del max
            }
        }

        P.posicion(pos)->info = P.posicion(i)->info; // mueve la primer posicion del subconjunto a la posicion del max
        m++; // (n-1) movimientos
        P.posicion(i)->info = max; // mueve el max a la primer posicion del subconjunto [i:N]
        m++;  // (n-1) movimientos
    }
}


int mapear(ArbolPosicional &P, ArbolAVL *T){
    int N = 0;
    ArbolAVL* lista = new ArbolAVL;
    lista = T;
    while (lista->last() != NULL)
    {
      P.CreaArbolPos(lista->last());
      lista = lista->resto();
      N++;
    }
    return N;
}
    

void leer_archivo(string archivo_,  ArbolAVL &T){
    string palabra;
    ifstream archivo(archivo_);
    if (archivo.is_open() ){
        char c;
        while(archivo.get(c)){
            if (isalnum(c)){
              palabra += c;  
            } else if (!palabra.empty())
            {    
                T.CreaArbolAVL(palabra);
                palabra = ""; 
            }   
        }
        archivo.close();
    }
}


