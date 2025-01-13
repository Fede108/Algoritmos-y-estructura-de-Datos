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
 //   stack<Nodo*> pila;
    void ArbolPos(ArbolAVL *&T, Nodo*& nuevo, int altura); // modifica el puntero lista (que es copia del original) usando *&T  
    void imprimir(Nodo* NodoAbb);           // imprime las hojas del arbol
    int calcularAltura(int numElementos);   // calcula altura del arbol segun nro elementos de la lista
    void show(Nodo* aux, int n);            // imprime el arbol 
public:
    ArbolPosicional(){
          raiz = NULL;
    //    raiz=new Nodo;
    //    raiz->altura = 1;
    //    pila.push(raiz);  
    };
    void CreaArbolPos(ArbolAVL *lista) // recibe una copia del puntero llamado lista, no puede modificar direccion del original
    {  
        ArbolPos(lista,raiz,calcularAltura(lista->last()->n));     // crea arbolPos en una llamada segun cantidad nodos de lista
    };
    void ImprimirHojas(){imprimir(raiz);};
    void swap(int p1, int p2);    
    NodoAbb* recorrer(int bin, Nodo* Nodo);
    Dato* posicion(int p);
    void verArbol(){ show(raiz,0);}
};

void ArbolPosicional::show(Nodo* aux, int n){    // recorrido dri 
     if (aux != NULL) {
        show(aux->der, n+1);
        for(int i=1; i<=n; i++) cout <<"        ";   // imprime nodo con espacio n inversamente proporcional segun altura nodo
        if(aux->hoja) cout  << "   "<< aux->hoja->info->palabra << "\n"; 
        else cout  << "nodInt h="<<aux->altura << "\n";
        show(aux->izq, n+1);
    }
}

NodoAbb* ArbolPosicional::recorrer(int bin, Nodo* Nodo)
{
    while (Nodo->altura > 0)
    {
        int bit = (bin >> (Nodo->altura - 1)) & 1;   // toma el bit del numero segun altura del nodo 
        if (bit) { 
        Nodo = Nodo->der; // recorre por el lado derecho 
        } else { 
        Nodo = Nodo->izq; // recorre por el lado izquierdo
        }
        if(Nodo == NULL) return nullptr;
    }
    return Nodo->hoja;
}    

void ArbolPosicional :: swap(int p1, int p2){   // intercambia el contenido de los nodos
    p1 = p1 - 1;
    p2 = p2 - 1;
    Dato* tmp  = recorrer(p2, raiz)->info;
    recorrer(p2, raiz)->info = recorrer(p1, raiz)->info;
    recorrer(p1, raiz)->info = tmp;
}

Dato* ArbolPosicional :: posicion(int p){    // devuelve contenido del nodo segun int p
    p = p - 1;    
    return recorrer(p,raiz)->info;
}

void ArbolPosicional ::imprimir(Nodo* Nodo)    // recorrido id
{
    if (Nodo == NULL) return;
    if (Nodo->altura == 0)
    {
        printf("%-10s %5i %5i\n", Nodo->hoja->info->palabra.c_str(), Nodo->hoja->info->repeticiones, Nodo->hoja->n);
        return;
    }
    imprimir(Nodo->izq);
    imprimir(Nodo->der);
}

int ArbolPosicional :: calcularAltura(int nroNodo) {  // La formula log2(n) determina cuántos niveles (o altura) necesita un arbol completo
    int altura = 0;
    while (nroNodo > 0) {
        nroNodo = nroNodo / 2; // dividir por 2 en cada iteración equivalente log2(n) + 1
        // dividir por 2 es equivalente a subir un nivel en el árbol
        altura++;    // aumento de a uno la altura subiendo de nivel
    }
    return altura;     
}

 void ArbolPosicional :: ArbolPos(ArbolAVL *&T, Nodo*& nuevo, int altura) { // crea el arbol posicional en una sola llamada O(2^n)
    if (!nuevo && altura == 0 && T->last()->siguiente) {  // si la altura es 0 crea nodo hoja
        nuevo = new Nodo;
        nuevo->altura = altura;
        nuevo->hoja = T->last();   
        T = T->resto();     // se desplaza al siguiente nodo mas reciente
        return;
    }else if (!nuevo && altura != 0 ) {    // crea nodo interno
        nuevo = new Nodo;
        nuevo->altura = altura;
    } 
    else  { return; }
    // recorrido id 
    // se construye el arbol desde el nivel inferior hacia niveles superiores
    ArbolPos(T, nuevo->izq,  altura - 1);
    ArbolPos(T, nuevo->der,  altura - 1);
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

//--------------------------------------------------------------------------------------------


void ordenaSeleccion(ArbolPosicional &P,int N,int &cm, int &cc);
void mapear(ArbolPosicional &P, ArbolAVL *T);
void leer_archivo(string archivo_,  ArbolAVL &T);
void ordenaQuickSort(ArbolPosicional &P, int primero, int ultimo,int &cm, int &cc);
string convertirMayuscula(string palabra);
void salida();

int main(){
    int cm1 = 0, cc1=0, cm2 = 0, cc2=0, N = 0;
    ArbolAVL T;
    ArbolAVL *T_copy;
    ArbolPosicional P;
    leer_archivo("data.txt", T);
    N = T.last()->n + 1;
    T_copy = T.Copy();
    //T.VerArbol();
    salida(); cout <<"IRD original"<<endl;
    T.IRD(); cout<<endl;

    cout <<"Arbol pos semicompleto"<<endl;
    mapear(P, &T);
    P.verArbol();
 
    ordenaSeleccion(P,N,cm1,cc1);
    salida(); cout <<"Hojas ordenadas seleccion"<<endl;
    P.ImprimirHojas();
    salida(); cout <<"Hojas ordenadas quick"<<endl;
    ordenaQuickSort(P,1,N,cm2,cc2);
    P.ImprimirHojas();

    salida(); cout <<"IRD copia"<<endl;
    T_copy->IRD();

    cout << "\n " <<" algoritmo seleccion: nro movimientos = "<<cm1<<" nro de comparaciones = "<<cc1<<endl;
    cout << "\n" <<"  algoritmo quickSort: nro movimientos = "<<cm2<<" nro de comparaciones = "<<cc2<<endl;
    

    cout<<endl;system("PAUSE");
}

void salida(){
    cout << "\n";
    cout << "\n";
    cout << "palabra " << "repeticiones " << "nro nodo----";
   
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
    
        pos = i; // supone el max como primer posicion subconjunto [i:N-1]

        for(j=i+1;j<=N;j++){  // recorre el subconjunto [i+1:N] n-1 veces
            cc++; // n-i-1 comparaciones 
            if( P.posicion(j)->repeticiones > P.posicion(pos)->repeticiones ){ // si encuentra un elemento con mas repeticiones

                pos = j; // actualiza posicion del max del subconjunto

            }
        }

        P.swap(pos,i);  // intercambia la primer posicion del subconjunto [i:N] con el max 
        cm = cm + 3; // 3(n-1) movimientos
    }
}


void mapear(ArbolPosicional &P, ArbolAVL *T){  
    P.CreaArbolPos(T);                                                                      
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
