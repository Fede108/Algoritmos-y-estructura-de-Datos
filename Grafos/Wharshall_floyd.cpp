#include <cstdlib>
#include <iostream>
#define INFI  9000
#define MAXNODOS  4


void warshall(int peso[][MAXNODOS], int caminos[][MAXNODOS]);
void Floyd(int peso[][MAXNODOS], int A[][MAXNODOS],int cf[][MAXNODOS]);
void caminoFloyd(int cf[][MAXNODOS], int s, int t);
int caminoOptimo(int destino, int* tabla);

using namespace std;

int main(int argc, char *argv[])
{   int peso[MAXNODOS][MAXNODOS]={INFI, 3,    INFI,   10, 
                                  INFI, INFI,    1,   INFI, 
                                  INFI, INFI, INFI,    2,  
                                  INFI, INFI, INFI, INFI,     
                                 };
    int caminos[MAXNODOS][MAXNODOS];
    int cf[MAXNODOS][MAXNODOS];
    int MatrizFloyd[MAXNODOS][MAXNODOS];
    int *pdist, i, j, precede[MAXNODOS],s,t;
    
    s=0;  // vertice de inicio
    t=3;  // vertice final  
    
    cout<<endl<<"Matriz de pesos";   
    for(i=0;i<MAXNODOS;i++){
           cout<<"\n";                 
           for(j=0;j<MAXNODOS;j++){
                  printf(" %5i",peso[i][j]);                 
           }                 
    }
    
    warshall(peso,caminos);
    cout<<"\n\n";
    cout<<"\n WARSHALL ------------------------\n";
    for(i=0;i<MAXNODOS;i++){
           cout<<"\n";                 
           for(j=0;j<MAXNODOS;j++){
                  printf(" %5i",caminos[i][j]); 
           }//fin for j                 
    }//fin for i
    cout<<"\n\n";
    if(caminos[s][t]==1){
                         cout<<"\n HAY CAMINO ENTRE s= "<<s
                             <<" y t= "<<t<<endl;
                         Floyd(peso,MatrizFloyd,cf);
                         cout<<"\n costo para ir de "
                             <<s<<" a "<<t<<"= "
                             <<MatrizFloyd[s][t];
                         cout<<"\n\n camino:  "<<s;
                         caminoFloyd(cf,s,t);
                         cout<<"  "<<t;  
                     
                     cout<<"\n\n"<<caminoOptimo(0,cf[3]);
    }
   
    else{
          cout<<"\n NO HAY CAMINO POSIBLE ENTRE s= "
              <<s<<" y t= "<<t<<endl;
          
    }//fin if

    cout<<endl<<endl<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}

void warshall(int peso[][MAXNODOS], int caminos[][MAXNODOS])
{ int i,j,k;
//inicializo caminos haciendola igual a la adjunta impl�cita en peso  
  for(i=0;i<MAXNODOS;i++){
         for(j=0;j<MAXNODOS;j++){
                if(peso[i][j]==INFI)caminos[i][j]=0;
                else                caminos[i][j]=1;
         }//fin for j
  }//fin for i
  
  for(k=0;k<MAXNODOS;k++){
         for(i=0;i<MAXNODOS;i++){
                for(j=0;j<MAXNODOS;j++){                 
                                if(caminos[i][j]==0) 
                                   caminos[i][j]=caminos[i][k]&&caminos[k][j];
                }//fin for j
         }//fin for i
  }//fin for k
}//fin warshall     

void Floyd(int peso[][MAXNODOS], int A[][MAXNODOS], int cf[][MAXNODOS])
{ int i,j,k;
  for(i=0;i<MAXNODOS;i++){
         for(j=0;j<MAXNODOS;j++){
                                 A[i][j]=peso[i][j];
                                 if(peso[i][j] == INFI) cf[i][j]=-1;
                                 else cf[i][j]=j;
         }
  }
  for(i=0;i<MAXNODOS;i++) A[i][i]=0;
  
  for(k=0;k<MAXNODOS;k++){
      for(i=0;i<MAXNODOS;i++){
         for(j=0;j<MAXNODOS;j++){
                                 if((A[i][k]+ A[k][j])< A[i][j]){
                                              A[i][j]= A[i][k]+ A[k][j];
                                              cf[i][j]=k;
                                 }
         }
      }
  }
    cout<<"\n FLOYD ------------------------\n";    
    for(i=0;i<MAXNODOS;i++){
           cout<<"\n";                 
           for(j=0;j<MAXNODOS;j++){
                  printf(" %5i",A[i][j]);                 
           }                 
    }

     for(i=0;i<MAXNODOS;i++){
           cout<<"\n";                 
           for(j=0;j<MAXNODOS;j++){
                  printf(" %5i",cf[i][j]);                 
           }                 
    }
    cout<<endl;
}

void caminoFloyd(int cf[][MAXNODOS], int s, int t)
{ int k;

  if(cf[s][t] == -1){ cout<<"no hay camino"; return;}
  k=cf[s][t];
  if (k!=t){
            caminoFloyd(cf,s,k);
            cout<<"  "<<k;
            caminoFloyd(cf,k,t);
            }
}

int caminoOptimo(int destino, int tabla[]){
       if(tabla[destino] == -1){
         cout<< "no hay camino "; return 0;}
       if(destino == tabla[destino]) return destino;
       destino = tabla[destino]; 
       return caminoOptimo(destino, tabla);
}
