#include <stdio.h>
#include <iostream>
#include <conio.h>

using namespace std;

typedef int tarbol;
struct nodoAVL{
       tarbol dato; // de tipo arbol
       int FB; // FB es la altura del subarbol izq menos la altura del subarbol der
       nodoAVL *izq, *der;
};

typedef nodoAVL * pnodo;
class arbolAVL{
    pnodo raiz;
    void Insert(int x, bool &aumento, nodoAVL* &A);
    void show(pnodo aux, int n);
    void rotarLL(nodoAVL* &A);
    void rotarRR(nodoAVL* &A);
    void rotarLRalter(nodoAVL* &A);
    void rotarRLalter(nodoAVL* &A);
    
public:
    arbolAVL(){raiz=NULL;};
    ~arbolAVL(){};
    void CreaArbolAVL(tarbol x);
    void VerArbol(){ show(raiz,0); }
};

void arbolAVL::CreaArbolAVL(tarbol x)
{    bool aumento;
     aumento=false;
     Insert(x,aumento,raiz);
}

void arbolAVL::Insert(int x, bool &aumento, nodoAVL* &A){
        if (A == NULL){
                A = new nodoAVL;
                A->dato = x;
                A->FB = 0;
                A->izq = NULL;
                A->der = NULL;
                aumento = true;
        }else{
                if (x < A->dato){                       
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
                                        // cargado hacia la izquierda
                                        case 1:{
                                                if (A->izq->FB == 1){ //1 necesita RR, si es -1 necesita RL
                                                       
                                                        rotarRR(A);
                                                }else{
                                                      
                                                        rotarRLalter(A);
                                                }
                                                aumento = false;
                                                break;
                                        }
                                }//fin switch
                        }//fin aumento==true
                }//fin subarbol izquierdo
                else{
                        Insert(x, aumento, A->der);                     
                        if (aumento){
                                switch (A->FB){
                                        // cargado hacia la derecha
                                        case -1:{
                                                if (A->der->FB == 1){ //1 necesita RL, si es -1 necesita LL
                                                          rotarLRalter(A);
                                                }else{
                                                         rotarLL(A);
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
        }//fin A!=NULL
}

// B<A 
void arbolAVL::rotarRR(nodoAVL* &A){ 
        cout<<"\n Rotacion RR"<<endl;
        nodoAVL* B   = A->izq;   // B a la izq A
        nodoAVL* aux = B->der;   // hijo derecho de nueva raiz 
        B->der = A;              // A se inserta a der B (nueva raiz)             
        B->FB = 0;                 
        A->izq = aux;            // hijo der de B se inserta izq de A  (sigue estando der de B y izq A)
        A->FB = 0;
        A = B;                   // B es nueva raiz
}

// B<A
void arbolAVL::rotarLL(nodoAVL* &B){  
        cout<<"\n Rotacion LL"<<endl;
        nodoAVL* A   = B->der;   // A esta a la der B
        nodoAVL* aux = A->izq;   // hijo izquierdo de nueva raiz
        A->izq = B;              // B se inserta a izq de A              
        A->FB = 0;                 
        B->der = aux;            // hijo izq de A se inserta der de B (sigue estando izq de A y der B)
        B->FB = 0;
        B = A;                   // A es nueva raiz
}

 
void arbolAVL::rotarLRalter(nodoAVL* &A){ 
        cout<<"\n Rotacion Doble RR+LL"<<endl;
        rotarRR(A->der);
        VerArbol();
        rotarLL(A);
}
 
void arbolAVL::rotarRLalter(nodoAVL* &A){ 
        cout<<"\n Rotacion Doble LL+RR"<<endl;
        rotarLL(A->izq);
        VerArbol();
        rotarRR(A);
}

void arbolAVL::show(pnodo aux, int n)
{ int i;
   if(aux!=NULL){                      //OjO este es un recorrido dri
       show(aux->der, n+1);
       for(i=1; i<=n; i++) cout<<"        ";
       cout<<"("<<aux->dato<<" "<<aux->FB<<")"<<"\n";
       show(aux->izq, n+1);
   }
}
//-------------------------------------------------------
int main (int argc, char *argv[])
{  int i; tarbol x;
   arbolAVL T;
   int vec[9]={50,120,180,240,270,360,410,425,550};
   for(i=0;i<9;i++){ 
                      T.CreaArbolAVL(vec[i]);
                      T.VerArbol();
                      
   } 
                     
   T.VerArbol();
  
   cout<<endl;
//   system("PAUSE");
//   return EXIT_SUCCESS;
}