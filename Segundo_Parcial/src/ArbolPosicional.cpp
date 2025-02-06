#include "../inc/ArbolPosicional.h"

using namespace std;

void ArbolPosicional::show(Nodo* aux, int n){    // recorrido dri 
     if (aux != NULL) {
        show(aux->der, n+1);
        for(int i=1; i<=n; i++) cout <<"        ";   // imprime nodo con espacio n inversamente proporcional segun altura nodo
        if(aux->hoja) cout  << "   "<< aux->hoja->info->palabra << "\n"; 
        else cout  << "nodInt h="<<aux->altura << "\n";
        show(aux->izq, n+1);
    }
}

NodoAbbLista* ArbolPosicional::recorrer(int n, Nodo* Nodo)
{
    convertirBin(n);
    while (Nodo->altura > 0)
    {     
        int bit = pila.tope(); pila.desapilar();
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
    NodoAbbLista* NodoP2 = recorrer(p2, raiz);
    NodoAbbLista* NodoP1 = recorrer(p1, raiz);
    Dato* tmp = NodoP2->info;       
    NodoP2->info = NodoP1->info;    
    NodoP1->info = tmp;             
}

Dato* ArbolPosicional :: posicion(int p){    // devuelve contenido del nodo segun int p
    p = p - 1;    
    return recorrer(p,raiz)->info;
}

void ArbolPosicional::convertirBin(int n){
    int i = raiz->altura;  // nro de bits que debe tener el binario
    while(n>0){
        pila.apilar(n%2);   
        n = n/2;
        i--;
    }
    while(i>0){     // se completa con ceros
        pila.apilar(0);
        i--;
    }
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

int ArbolPosicional :: calcularAltura(int nroNodo) {  // la altura equivale a cuantas veces puedo dividir en 2 al nro nodos
    int altura = 0;
    while (nroNodo > 0) {    
        nroNodo = nroNodo / 2;  // divido por 2 en cada iteracion 
        altura++;               // aumento de a uno la altura del arbol
    }
    return altura;     
}

 void ArbolPosicional :: ArbolPos(ListaConAbb *&T, Nodo*& nuevo, int altura) { // crea el arbol posicional en una sola llamada O(2^n) = O(N)
    if(!nuevo){
        if (altura == 0 && T->cabeza()->siguiente) {  // si la altura es 0 crea nodo hoja
            nuevo = new Nodo;
            nuevo->altura = altura;
            nuevo->hoja = T->cabeza();   
            T = T->resto();           // se desplaza al siguiente nodo mas reciente
            return;
        } else if (altura > 0) {      // crea nodo interno
            nuevo = new Nodo;
            nuevo->altura = altura;
        }
        else  { return; }
    } 
    
    // recorrido rid 
    ArbolPos(T, nuevo->izq,  altura - 1);
    ArbolPos(T, nuevo->der,  altura - 1);
}

/* void ArbolPosicional :: ArbolPos(NodoAbbLista *lista, Nodo*& nuevo){  
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
