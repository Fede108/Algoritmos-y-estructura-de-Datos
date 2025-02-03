#include "../inc/ListaConABB.h"

//------------------------------------ metodos de lista -----------------------------------------------------

ArbolAVL* ArbolAVL::resto(){
        ArbolAVL* aux = new ArbolAVL();
        aux->czo = this->czo->siguiente;
        return (aux);
}

NodoAbb* ArbolAVL::last(){
        return czo;
}

void ArbolAVL::impre(NodoAbb* aux){
    if (aux->siguiente != NULL) {
        cout << "\n" << aux->info->palabra <<" "<<aux->info->repeticiones<<" "<<aux->n;
        impre(aux->siguiente);
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
        if (aux->siguiente != NULL)
        { 
                copy(aux->siguiente, arbol);
                arbol->CreaArbolAVL(aux->info->palabra); 
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
                if(A->siguiente) A->n = A->siguiente->n + 1; // seteo nro de nodo
                aumento = true;        
        }else{
                if (x < A->info->palabra){    // si la palabra 'x' es menor, se inserta en el subárbol izquierdo                    
                        Insert(x, aumento, A->izq);                     
                        if (aumento){
                                switch (A->FB){
                                        case -1:{
                                                A->FB = 0;  // se balanceo la raiz con insercion izq
                                                aumento = false; // no aumento la altura
                                                break;
                                        }
                                        case 0:{
                                                A->FB = 1;
                                                aumento = true;  // aumento la altura hacia la izq
                                                break;
                                        }
                                        case 1:{  // aumento la altura hacia la izq 
                                                  // se balancea la raiz con rotacion der
                                                if (A->izq->FB == 1){ //1 necesita RR, si es -1 necesita RL
                                                        rotarRR(A);
                                                }else{
                                                        rotarRLalter(A);
                                                        
                                                }
                                                aumento = false;   // fb = 0, no aumento la altura del arbol
                                                break;
                                        }
                                }//fin switch
                        }//fin aumento==true
                }//fin subarbol izquierdo
                else if (x > A->info->palabra){   // si la palabra 'x' es mayor, se inserta en el subárbol derecho
                        Insert(x, aumento, A->der);                     
                        if (aumento){
                                switch (A->FB){         
                                        case -1:{  // aumento la altura hacia la der  
                                                // se balancea la raiz con rotacion izq
                                                if (A->der->FB == 1){ //1 necesita LR, si es -1 necesita LL
                                                        rotarLRalter(A);
                                                }else{
                                                        rotarLL(A);
                                                }
                                                aumento = false;   // fb = 0, no aumento la altura del arbol                                              
                                                break;
                                        }
                                        case 0:{
                                                A->FB = -1;      
                                                aumento = true;  // aumento la altura del arbol hacia der
                                                break; 
                                        }
                                        case 1:{
                                                A->FB = 0;      // se balanceo la raiz con insercion der
                                                aumento = false;   // no aumenta la altura
                                                break;
                                        }
                                }//fin switch
                        }//fin aumento==true
                }//fin subarbol derecho
                else{ 
                        A->incrContador();  // Si la palabra ya existe, se incrementa el contador de repeticiones
                }
        }//fin A!=NULL
}

// A>B 
void ArbolAVL::rotarRR(NodoAbb* &A){ 
        NodoAbb* B = A->izq;     // nueva raiz B a la izq A
        NodoAbb* aux = B->der;   // guarda hijo derecho de B 
        B->der = A;              // A se inserta a der B  nueva raiz (A->izq)             
        B->FB = 0;                 
        A->izq = aux;            // hijo der de B se inserta izq de A  (sigue estando der de nueva raiz y izq A)
        A->FB = 0;
        A = B;                   // B es nueva raiz
}

// A>B
void ArbolAVL::rotarLL(NodoAbb* &B){  
        NodoAbb* A = B->der;     // nueva raiz A esta a la der B
        NodoAbb* aux = A->izq;   // guarda hijo izquierdo de A
        A->izq = B;              // B se inserta a izq de A              
        A->FB = 0;                 
        B->der = aux;            // hijo izq de A se inserta der de B (sigue estando izq de A y der B)
        B->FB = 0;
        B = A;                   // A es nueva raiz
}
 
void ArbolAVL::rotarLRalter(NodoAbb* &A){ 
        rotarRR(A->der);
        rotarLL(A);
}
 
void ArbolAVL::rotarRLalter(NodoAbb* &A){ 
        rotarLL(A->izq);
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