#include "../inc/ListaConABB.h"

//------------------------------------ metodos de lista -----------------------------------------------------

ArbolAVL* ArbolAVL::resto(){
        ArbolAVL* aux = new ArbolAVL();
        aux->czo = this->czo->siguiente;
        return (aux);
}

NodoAbb* ArbolAVL::cabeza(){
        return czo;
}

void ArbolAVL::impre(NodoAbb* aux){
    if (aux->siguiente != NULL) {
        impre(aux->siguiente);
        printf("%-10s %5i %5i\n", aux->info->palabra.c_str(), aux->info->repeticiones, aux->n);
    }
}

//------------------------------------ metodos de arbol -----------------------------------------------------

void ArbolAVL::CreaArbolAVL(string x)
{    bool aumento;
     aumento=false;
     Insert(x,aumento,raiz);
}

void ArbolAVL::ird(NodoAbb* aux)
{
    if (aux != NULL) {
        ird(aux->izq);
        printf("%-10s %5i %5i\n", aux->info->palabra.c_str(), aux->info->repeticiones, aux->n);
        ird(aux->der);
    }
}

ArbolAVL* ArbolAVL::copy(NodoAbb* aux, ArbolAVL* &arbol){
        if (aux != NULL) {
        copy(aux->izq, arbol);
        NodoAbb* A = new NodoAbb(aux->info->palabra, aux->info->repeticiones,aux->n);
        A->setNext(arbol->czo);
        arbol->czo = A;
        copy(aux->der, arbol);
    }
    return arbol;
}

void ArbolAVL::Insert(string x, bool &aumento, NodoAbb* &A){
        if (A == NULL){
                A = new NodoAbb(x);
                A->FB = 0;
                A->izq = NULL;
                A->der = NULL;
                A->setNext(czo);  // sumar NodoAbbs a la lista
                czo = A;          // Actualizar la cabeza de la lista
                A->n = A->siguiente->n + 1; // seteo nro de nodo
                aumento = true;        
        }else{
                if (x < A->info->palabra){    // si la palabra 'x' es menor alfabeticamente, se inserta en el subarbol izquierdo                    
                        Insert(x, aumento, A->izq);                     
                        if (aumento){
                                switch (A->FB){
                                        case -1:{ // cargado hacia der
                                                A->FB = 0;  // se balanceo la raiz con insercion izq
                                                aumento = false; // no aumento la altura
                                                break;
                                        }
                                        case 0:{
                                                A->FB = 1;
                                                aumento = true;  // aumento la altura hacia la izq
                                                break;
                                        }
                                        case 1:{  // cargado hacia la izquierda
                                                  // se balancea la raiz con rotacion der
                                                if (A->izq->FB == 1){ // 1 necesita RR, si es -1 necesita LR
                                                        rotarRR(A);
                                                }else{
                                                        rotarLRalter(A);
                                                        
                                                }
                                                aumento = false;   // fb = 0, no aumento la altura del arbol
                                                break;
                                        }
                                }//fin switch
                        }//fin aumento==true
                }//fin subarbol izquierdo
                else if (x > A->info->palabra){   // si la palabra 'x' es mayor alfabeticamenete, se inserta en el subarbol derecho
                        Insert(x, aumento, A->der);                     
                        if (aumento){
                                switch (A->FB){     
                                        case -1:{ // cargado hacia la derecha    
                                                  // se balancea la raiz con rotacion izq
                                                if (A->der->FB == 1){ // 1 necesita RL, si es -1 necesita LL
                                                        rotarRLalter(A);
                                                }else{
                                                        rotarLL(A);
                                                }
                                                aumento = false;    // fb = 0, no aumento la altura del arbol                                              
                                                break;
                                        }
                                        case 0:{
                                                A->FB = -1;      
                                                aumento = true;  // aumento la altura del arbol hacia der
                                                break; 
                                        }
                                        case 1:{ // cargado hacia izq
                                                A->FB = 0;         // se balanceo la raiz con insercion der
                                                aumento = false;   // no aumenta la altura
                                                break;
                                        }
                                }//fin switch
                        }//fin aumento==true
                }//fin subarbol derecho
                else{ 
                        A->incrContador();  // si la palabra ya existe, se incrementa el contador de repeticiones
                }
        }//fin A!=NULL
}

// A<-B 
void ArbolAVL::rotarRR(NodoAbb* &B){ 
        NodoAbb* A   = B->izq;   // nueva raiz A a la izq B
        NodoAbb* aux = A->der;   // guardo subarbol derecho de A 
        A->der = B;              // B se inserta a der A              
        A->FB = 0;                 
        B->izq = aux;            // hijo der de A se inserta izq de B  (sigue estando der de A y izq B)
        B->FB = 0;
        B = A;                   // A es nueva raiz
}

// A->B 
void ArbolAVL::rotarLL(NodoAbb* &A){  
        NodoAbb* B   = A->der;   // nueva raiz B esta a la der A
        NodoAbb* aux = B->izq;   // guardo subarbol izquierdo de B
        B->izq = A;              // A se inserta a izq de B              
        B->FB = 0;                 
        A->der = aux;            // hijo izq de B se inserta der de A (sigue estando izq de B y der A)
        A->FB = 0;
        A = B;                   // B es nueva raiz
}

 
void ArbolAVL::rotarRLalter(NodoAbb* &A){ // raiz cargada hacia der
        rotarRR(A->der);                  // hijo der se encuentra cargado hacia izq
        rotarLL(A);
}
 
void ArbolAVL::rotarLRalter(NodoAbb* &A){ // raiz cargada hacia izq
        rotarLL(A->izq);                  // hijo izq se encuentra cargado hacia der
        rotarRR(A);
}

void ArbolAVL::show(NodoAbb* aux, int n)
{ 
int i;
    if(aux!=NULL){                      //OjO este es un recorrido dri
       show(aux->der, n+1);
       for(i=1; i<=n; i++) cout<<"        ";
       cout<<"("<<aux->info->palabra<<" "<<aux->FB<<")"<<"\n";
       show(aux->izq, n+1);
   }
}

/*void ArbolAVL::show_(Cola<NodoAbb*>* cola, int n)
{ 
        int i;
        while(cola->esvacia()){
                for(i=1; i<=(czo->n-cola->size()); i++) cout<<"        ";
                        cout<<"("<< cola->tope()->info->palabra<<" "<<cola->tope()->FB<<")";
                        cola->desencolar();
        }
        cout<<"\n";
        cola->encolar(cola->tope()->izq);
        cola->encolar(cola->tope()->der);
        show_()    
        }
} */
