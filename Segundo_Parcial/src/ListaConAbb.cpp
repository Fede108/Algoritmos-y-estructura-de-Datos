#include "../inc/ListaConABB.h"

void ArbolAVL::CreaArbolAVL(string x)
{    bool aumento;
     aumento=false;
     Insert(x,aumento,raiz);
}

void ArbolAVL::ird(Nodo* aux)
{
    if (aux != NULL) {
        ird(aux->izq);
        cout << "\n" << aux->info->palabra;
        ird(aux->der);
    }
}

void ArbolAVL::impre(Nodo* aux){
    if (aux != NULL) {
        cout << "\n" << aux->info->palabra;
        impre(aux->siguiente);
    }
}

ArbolAVL* ArbolAVL::copy(Nodo* aux, ArbolAVL* &arbol){
        if (aux != NULL)
        { 
                copy(aux->izq, arbol);
                arbol->CreaArbolAVL(aux->info->palabra); 
                copy(aux->der, arbol);
        } 
        return arbol;     
}

void ArbolAVL::Insert(string x, bool &aumento, Nodo* &A){
        if (A == NULL){
                A = new Nodo(x);
                A->FB = 0;
                A->izq = NULL;
                A->der = NULL;
                A->setNext(czo);  // sumar nodos a la lista
                czo = A;
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

void ArbolAVL::rotarLL(Nodo* &A){ 
        cout<<"\n LL>> "<<A->info->palabra<<endl<<endl;
        Nodo* aux = A->izq->der;
        A->izq->der = A;
        A->izq->FB = 0; 
        Nodo* aux2 = A->izq;
        A->izq = aux;
        A->FB = 0;
        A = aux2;
}
 
void ArbolAVL::rotarRR(Nodo* &A){ 
        cout<<"\n RR>> "<<A->info->palabra<<endl<<endl;
        Nodo* aux = A->der->izq;
        A->der->izq = A;
        A->der->FB = 0; 
        Nodo* aux2 = A->der;
        A->der = aux;
        A->FB = 0;
        A = aux2;
}
 
void ArbolAVL::rotarLRalter(Nodo* &A){ 
        cout<<"\n Rotacion Doble RR+LL"<<endl;
        rotarRR(A->izq);
        VerArbol();
        rotarLL(A);
}
 
void ArbolAVL::rotarRLalter(Nodo* &A){ 
        cout<<"\n Rotacion Doble LL+RR"<<endl;
        rotarLL(A->der);
        VerArbol();
        rotarRR(A);
}

void ArbolAVL::show(Nodo* aux, int n)
{ 
int i;
    if(aux!=NULL){                      //OjO este es un recorrido dri
       show(aux->der, n+1);
       for(i=1; i<=n; i++) cout<<"        ";
       cout<<"("<<aux->info->palabra<<" "<<aux->FB<<")"<<"\n";
       show(aux->izq, n+1);
   }
}

