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
    int calcularAltura(int numElementos);
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
        if (msb) { 
            Nodo = Nodo->der; // recorre por el lado derecho 
        } else { 
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

void ArbolPosicional ::imprimir(Nodo* Nodo)
{
    if(Nodo == NULL) return;
    if (Nodo->altura == 0)
    {
        cout<<Nodo->hoja->info->palabra<<" "<<Nodo->hoja->info->repeticiones<<" "<<Nodo->hoja->n<<endl;
        return;
    }
    imprimir(Nodo->izq);
    imprimir(Nodo->der);
}

int calcularAltura(int numElementos) {
    int altura = 0;
    while ((1 << altura) < numElementos) {
        altura++;
    }
    return altura;
}

void ArbolPos(ArbolAVL *T, Nodo*& nuevo, int altura) {
    if (!nuevo) {
        nuevo = new Nodo;
        nuevo->altura = altura;
    }

    if (altura == 0) {
        nuevo->hoja = T->last(); 
        return;
    }

    ArbolPos(T->resto(), nuevo->izq,  altura - 1);
    ArbolPos(T->resto(), nuevo->der,  altura - 1);
}


/* void ArbolPosicional :: ArbolPos(NodoAbb *lista, Nodo*& nuevo){  
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
    if (!pila.empty()) // sigue con el nivel superior
    {
        ArbolPos(lista, pila.top());
        return;
    }
    // si se completaron los niveles se crea una nueva raíz
    Nodo *nuevaRaiz = new Nodo; 
    nuevaRaiz->altura = raiz->altura + 1;
    nuevaRaiz->izq = raiz;
    raiz = nuevaRaiz;    
    ArbolPos(lista,nuevaRaiz);
}*/

//------------------------------------------------------------------------------------------


void ordenaSeleccion(ArbolPosicional &P,int N,int &cm, int &cc);
int mapear(ArbolPosicional &P, ArbolAVL *T);
void leer_archivo(string archivo_,  ArbolAVL &T);
void ordenaQuickSort(ArbolPosicional &P, int primero, int ultimo,int &cm, int &cc);
string convertirMayuscula(string palabra);

int main(){
    int cm1 = 0, cc1=0, cm2 = 0, cc2=0;
    ArbolAVL T;
    ArbolAVL *T_copy;
    ArbolPosicional P;
    leer_archivo("archivo_texto_tarea.txt", T);
    T_copy = T.Copy();
//    T.VerArbol();
//    T.IRD();
    cout << "\n";
    cout << "\n";
//    T.print();
//    T_copy->VerArbol();
    T_copy->IRD();
    cout << "\n";
    cout << "\n";
    int N = mapear(P, &T);
 //   P.ImprimirHojas();
    ordenaSeleccion(P,N,cm1,cc1);
//    P.ImprimirHojas();
    cout << "\n";
    cout << "\n";
    ordenaQuickSort(P,1,N,cm2,cc2);
//    P.ImprimirHojas();
    T.IRD();
    cout << "\n";
    cout << "\n" <<cm1<<" "<<cc1<<" "<<cm2<<" "<<cc2<<" ";
    

    cout<<endl;system("PAUSE");
}

void ordenaQuickSort(ArbolPosicional &P, int primero, int ultimo,int &cm, int &cc){
    int i,j;
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

            ordenaQuickSort(P,primero,i-1,cm,cc);
            ordenaQuickSort(P,i+1,ultimo,cm,cc);
             
      } //fin if 
}// fin ordena


void ordenaSeleccion(ArbolPosicional &P,int N,int &cm, int &cc){
    int i,j,pos;
    
    for(i=1;i<N;i++){ // recorro desde pos 1 a N-1
     //   max = P.posicion(i); // supone el max como primer posicion subconjunto [i:N-1]
        pos = i; 
    //    m++;  // n-1 movimientos

        for(j=i+1;j<=N;j++){  // recorre el subconjunto [i+1:N] n-1 veces
            cc++; // n-i-1 comparaciones 
            if( P.posicion(j)->repeticiones > P.posicion(pos)->repeticiones ){ // si encuentra un elemento con mas repeticiones
            //    max = P.posicion(j); // actualiza el max del subconjunto
               // m++; // aprox n/2 veces por iteracion en el peor caso, max a min 
                pos = j; // guarda posicion del max
            }
        }

        P.swap(pos,i);  // intercambia la primer posicion del subconjunto [i:N] con el max 
        cm = cm + 3; // 3(n-1) movimientos
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
            if (c != '\n' && c != ' ' && c != '\t'){
              palabra += c;  
            } else if (!palabra.empty())
            {    
                T.CreaArbolAVL(convertirMayuscula(palabra));
                palabra = ""; 
            }   
        }
        archivo.close();
    }
}

string convertirMayuscula(string palabra){
    string palabraMayus;
    for (int i = 0; i < palabra.length(); i++) {
             if (palabra[i] >= 'a' && palabra[i] <= 'z') {
                palabraMayus += palabra[i] - 32; // Convertir a mayúscula
            }else{
                palabraMayus += palabra[i]; // Mantener otros caracteres
            }
    }
    return palabraMayus;
}
