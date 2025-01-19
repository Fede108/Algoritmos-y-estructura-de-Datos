// "Estructuras de Datos y Algoritmos" Alfred Aho y otros pag 233
#include <cstdlib>
#include <iostream>
#include <iomanip>
#define INFI  999
#define INFI2 9999
#define MAXNODOS  6
#define MAX 20

using namespace std;
// almacena MAX-1 elementos
// cola circular
class Cola{
      private:
              int Q[MAX];
              int pi,pf;
  public:
      Cola(void){pi=0;pf=MAX-1;};
      //~Cola(void);
      int tope(){return Q[pi];};
      bool colavacia(){return pi==(pf+1)%MAX;};
      bool colallena(){return pi==(pf+2)%MAX;};
      void encolar(int a);
      void desencolar();
      int ultimo();
      string imprimir(string s);
};
//-------- Metodos de Cola --------------------
void Cola::encolar(int a)
{  if (!colallena()){
     pf=(pf+1)%MAX;
     Q[pf]=a; 
   }
   else cout<<"Cola llena"<<endl;  
}
void Cola::desencolar(void)
{  if (!colavacia())pi=(pi+1)%MAX;
   else cout<<"Cola vacia"<<endl;  
}
int Cola::ultimo(void)
{   return Q[pf];
}
string Cola::imprimir(string s)
{    if(!colavacia()){  
         //by Martin     
         for(int i=pi;i!=pf+1;i=(i+1)%MAX)cout<<Q[i]<<"--";
            
            }  
               
       return " <<< Q";
}
//------------------------------------------------------


Cola Prim2(int C[][MAXNODOS]);

int main(int argc, char *argv[])
{   int peso[MAXNODOS][MAXNODOS]={INFI,    6,    1,    5, INFI, INFI,
                                     6, INFI,    5, INFI,   3,  INFI,
                                     1,    5, INFI,    5,    6,    4,
                                     5, INFI,    5, INFI, INFI,    2,
                                  INFI,    3,    6, INFI, INFI,    5,
                                  INFI, INFI,    4,    2,    5, INFI      
                                 };
    
    int i, j, u, v;
    Cola Q;
   
    
    cout<<endl<<"Matriz de pesos";   
    for(i=0;i<MAXNODOS;i++){
           cout<<"\n";                 
           for(j=0;j<MAXNODOS;j++){
                  printf(" %5i",peso[i][j]);                 
           }                 
    }
    cout<<"\n----------------------------------------------\n";
    Q=Prim2(peso); 
    cout<<"\n----------------------------------------------\n";
    while(!Q.colavacia()){
      u=Q.tope();
      Q.desencolar();
      v=Q.tope();
      Q.desencolar();
      cout<<"Arista: "<<u<<" al: "<<v<<endl;
    }
    cout<<endl<<endl; 
    system("PAUSE");
    return EXIT_SUCCESS;
   
}   

Cola Prim2(int C[][MAXNODOS])
{ int mencosto[MAXNODOS];
  int mascerca[MAXNODOS];
  int i,j,k,min,x;
  Cola Aristas;
  for(i=0;i<MAXNODOS;i++){
                          mencosto[i]=C[0][i];
                          mascerca[i]=0;
  }
  //V contiene todos los vertices del grafo
  //S contiene el vertice inicial, en este caso 0  
  mencosto[0]=INFI2;                
  for(i=1;i<MAXNODOS;i++){
  	// busco el vertice mas cercano (que llamare k)
  	// en V-S para algun vertice en S
       min=mencosto[1];
       k=1;
       for(j=2;j<MAXNODOS;j++){
            if(mencosto[j]<min){
                min=mencosto[j];
                k=j;
            } 
       }  
	   cout<<endl<<endl;
       cout<<"el nodo "<<k<<" es el mas cercano a "<<mascerca[k]<<"    distancia "<<min<<endl;
       
	   mencosto[k]=INFI2; //se a�ade k en S
	   Aristas.encolar(mascerca[k]);//guardo las aristas
	   Aristas.encolar(k);
       for(j=1;j<MAXNODOS;j++){
            if((C[k][j]<mencosto[j])&&(mencosto[j]<INFI2)){
                 mencosto[j]=C[k][j];
                 mascerca[j]=k;
            }
       }
       for(x=0;x<MAXNODOS;x++){
       	  cout<<setw(6)<< mencosto[x]<<setw(6)<<mascerca[k]<<endl;
	   }
  }
  return Aristas;
}
