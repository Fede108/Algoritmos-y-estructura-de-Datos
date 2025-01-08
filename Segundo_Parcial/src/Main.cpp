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
    stack<Nodo*> pila;
    void ArbolPos(NodoAbb *lista, Nodo*& nuevo);
    void imprimir(Nodo* NodoAbb);
public:
    ArbolPosicional(){
        raiz=new Nodo;
        raiz->altura = 1;
        pila.push(raiz);  
    };
    void CreaArbolPos(NodoAbb *lista){ ArbolPos(lista,pila.top());};
    void ImprimirHojas(){imprimir(raiz);};
    void swap(int p1, int p2);
    NodoAbb* recorrer(int bin, Nodo* Nodo);
    Dato* posicion(int p);
};

NodoAbb* ArbolPosicional::recorrer(int bin, Nodo* Nodo)
{
    while (Nodo->altura > 0)
    {
        int msb = (bin >> (Nodo->altura - 1)) & 1;
        if (msb) { // Si el bit mas significativo es 1
            Nodo = Nodo->der; // recorre por el lado derecho 
        } else { // Si el bit mas significativo es 0
            Nodo = Nodo->izq; // recorre por el lado izquierdo
        }
      if(Nodo == NULL) return nullptr;
    }
    return Nodo->hoja;
}

void ArbolPosicional :: swap(int p1, int p2){
    p1 = p1 - 1;
    p2 = p2 - 1;
    Dato* tmp  = recorrer(p2, raiz)->info;
    recorrer(p2, raiz)->info = recorrer(p1, raiz)->info;
    recorrer(p1, raiz)->info = tmp;
}

Dato* ArbolPosicional :: posicion(int p){
    p = p - 1;    
    return recorrer(p,raiz)->info;
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
    if (!nuevo->izq)
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
    if (!nuevo->der)
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
    // Si se completo el nivel actual, crear una nueva raíz
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
void ordenaQuickSort(ArbolPosicional &P, int primero, int ultimo);

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
    P.ImprimirHojas();
    cout << "\n";
    cout << "\n";
    ordenaQuickSort(P,1,N);
    P.ImprimirHojas();
//    T.print();
    cout<<endl;system("PAUSE");
}

void ordenaQuickSort(ArbolPosicional &P, int primero, int ultimo){
    int i,j,k,cm,cc;
    Dato* aux;
    Dato* pivot;
      if(ultimo>primero){
            pivot = P.posicion(ultimo);cm++;
            
            i=primero; j=ultimo;    
            while (i < j) { // El bucle se detendrá cuando i >= j
                while (P.posicion(i)->palabra < pivot->palabra){
                    cc++;
                    i++;
                    if(i>ultimo) break;
                } 
                while (P.posicion(j)->palabra >= pivot->palabra){
                    cc++;
                    j--;
                    if(j<primero) break;
                }
                if (i < j) { // Solo intercambiar si i < j
                    P.swap(i,j);
                    cm += 3;
                }
            }
            // pivot se mueve a v[i]
            //  v[i] se mueve a pivot
            P.swap(i,ultimo);
            cm=cm+3;

            ordenaQuickSort(P,primero,i-1);
            ordenaQuickSort(P,i+1,ultimo);
             
      } //fin if 
}// fin ordena


void ordenaSeleccion(ArbolPosicional &P,int N){
    int i,j,pos,m=0,c=0;
    Dato* max;
    for(i=1;i<N;i++){ // recorro desde pos 1 a N-1

        max = P.posicion(i); // supone el max como primer posicion subconjunto [i:N-1]
        pos=i; m++;  // n-1 movimientos

        for(j=i+1;j<=N;j++){  // recorre el subconjunto [i+1:N] n-1 veces
            c++; // n-i-1 comparaciones 
            if( P.posicion(j)->repeticiones > max->repeticiones ){ // si encuentra un elemento con mas repeticiones
                max = P.posicion(j); // actualiza el max del subconjunto
                m++; // aprox n/2 veces por iteracion en el peor caso, max a min 
                pos = j; // guarda posicion del max
            }
        }

        P.swap(pos,i); 
 //       P.posicion(pos) = P.posicion(i); // mueve la primer posicion del subconjunto a la posicion del max
 //       m++; // (n-1) movimientos
 //       P.posicion(i) = max; // mueve el max a la primer posicion del subconjunto [i:N]
//        m++;  // (n-1) movimientos
    }
}


int mapear(ArbolPosicional &P, ArbolAVL *T){
    int N = 0;
    ArbolAVL* czo = T;
    while (czo->last() != NULL)
    {
      P.CreaArbolPos(czo->last());
      czo = czo->resto();
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


