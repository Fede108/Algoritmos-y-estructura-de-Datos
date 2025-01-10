#include "../inc/ListaConABB.h"

ArbolAVL* ArbolAVL::resto(){
        ArbolAVL* aux = new ArbolAVL();
        aux->czo = this->czo->siguiente;
        return (aux);
}

NodoAbb* ArbolAVL::last(){
        return czo;
}

void ArbolAVL::CreaArbolAVL(string x)
{    bool aumento;
     aumento=false;
     Insert(x,aumento,raiz);
}

void ArbolAVL::ird(NodoAbb* aux)
{
    if (aux != NULL) {
        ird(aux->izq);
        cout << "\n" << aux->info->palabra<<" "<<aux->info->repeticiones<<" "<<aux->n;
        ird(aux->der);
    }
}

void ArbolAVL::impre(NodoAbb* aux){
    if (aux->siguiente != NULL) {
        cout << "\n" << aux->info->palabra <<" "<<aux->info->repeticiones<<" "<<aux->n;
        impre(aux->siguiente);
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
                czo = A;
                if(A->siguiente) A->n = A->siguiente->n + 1; // seteo nro de nodo
                aumento = true;        
        }else{
                if (x < A->info->palabra){                       
                        Insert(x, aumento, A->izq);                     
                        if (aumento){
                                switch (A->FB){
                                        case -1:{
                                                A->FB = 0;
                                                aumento = false;
                                                break;
                                        }
                                        case 0:{
                                                A->FB = 1;
                                                aumento = true;
                                                break;
                                        }
                                        case 1:{
                                                if (A->izq->FB == 1){ //1 necesita LL, si es -1 necesita LR
                                                        rotarLL(A);
                                                }else{
                                                        rotarLRalter(A);
                                                }
                                                aumento = false;
                                                break;
                                        }
                                }//fin switch
                        }//fin aumento==true
                }//fin subarbol izquierdo
                else if (x > A->info->palabra){
                        Insert(x, aumento, A->der);                     
                        if (aumento){
                                switch (A->FB){
                                        case -1:{
                                                if (A->der->FB == 1){ //1 necesita RL, si es -1 necesita RR
                                                        rotarRLalter(A);
                                                }else{
                                                        rotarRR(A);
                                                }
                                                aumento = false;                                                
                                                break;
                                        }
                                        case 0:{
                                                A->FB = -1;
                                                aumento = true;
                                                break;
                                        }
                                        case 1:{
                                                A->FB = 0;
                                                aumento = false;
                                                break;
                                        }
                                }//fin switch
                        }//fin aumento==true
                }//fin subarbol derecho
                else{
                        A->incrContador();
                }
        }//fin A!=NULL
}

void ArbolAVL::rotarLL(NodoAbb* &A){ 
        NodoAbb* aux = A->izq->der;
        A->izq->der = A;
        A->izq->FB = 0; 
        NodoAbb* aux2 = A->izq;
        A->izq = aux;
        A->FB = 0;
        A = aux2;
}
 
void ArbolAVL::rotarRR(NodoAbb* &A){ 
        NodoAbb* aux = A->der->izq;
        A->der->izq = A;
        A->der->FB = 0; 
        NodoAbb* aux2 = A->der;
        A->der = aux;
        A->FB = 0;
        A = aux2;
}
 
void ArbolAVL::rotarLRalter(NodoAbb* &A){ 
        rotarRR(A->izq);
        rotarLL(A);
}
 
void ArbolAVL::rotarRLalter(NodoAbb* &A){ 
        rotarLL(A->der);
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

