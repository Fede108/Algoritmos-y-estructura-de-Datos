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
    NodoAbb* NodoP2 = recorrer(p2, raiz);
    NodoAbb* NodoP1 = recorrer(p1, raiz);
    Dato* tmp = NodoP2->info;       
    NodoP2->info = NodoP1->info;    
    NodoP1->info = tmp;             
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
//    if(!nuevo){
        if (altura == 0 && T->last()->siguiente) {  // si la altura es 0 crea nodo hoja
            nuevo = new Nodo;
            nuevo->altura = altura;
            nuevo->hoja = T->last();   
            T = T->resto();           // se desplaza al siguiente nodo mas reciente
            return;
        } else if (altura > 0) {    // crea nodo interno
            nuevo = new Nodo;
            nuevo->altura = altura;
        }
        else  { return; }
//    } 
    
    // recorrido rid 
    // se construye el arbol desde el nivel superior hacia niveles inferiores
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
