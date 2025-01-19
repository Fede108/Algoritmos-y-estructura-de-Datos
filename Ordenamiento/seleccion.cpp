// Metodo de Ordenamiento por Seleccion Directa
// Wirth pag. 68
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define MAX 5

void impre(int *v);

int main(int argc, char *argv[])
{int i,j,pos,men,m=0,c=0;
 int a[MAX] ={50,40,30,20,10}; //
/*/ for(i=0;i<MAX;i++){
                    a[i]=int(rand());
 }*/
 //impre(a);
 cout<<"\n---------------------------------"<<endl;
 for(i=0;i<MAX-1;i++){
    men=a[i]; pos=i; m++;  // n-1 movimientos

      for(j=i+1;j<MAX;j++){  // n-1 veces
          c++; // n-i-1 comparaciones 
          if(a[j]<men){ 
          men=a[j]; m++; // aprox n/2 veces por iteracion en el peor caso, max a min 
          pos=j;
        }
      }

   a[pos]=a[i]; m++; a[i]=men; m++ ; // 2*(n-1) movimientos
 }
  impre(a);
// ---------       Mmin= 3(n-1)
// C= 1/2(n**2-n)  Mmed= ??
// --------------  Mmax= (n**2/4)+3(n-1)
 
  printf("\n cantidad de comparaciones= %d  movimientos= %d",c,m);
  printf("\n\n");
  system("PAUSE");	
  return 0;
}
void impre(int *v)
{ int i;
  printf("\n");
  for(i=0;i<MAX;i++)
     printf("\n %3d   %3d",i,v[i]);
}