// Metodo de Ordenamiento por Insercion Directa
// Wirth pag. 65
#include <stdio.h>
#include <stdlib.h>
#define MAX 5000

void impre(int *v);

int main(int argc, char *argv[])
{int i,j,k,di,m=0,c=0;
 int a[MAX];//={50,40,30,20,10}; // peor caso ordenado al reves
 for(i=0;i<MAX;i++){
                    a[i]=int(rand());
 }
 impre(a);

 for(i=1;i<MAX;i++){
   j=i-1; di=a[i];            m++; c++;
   while(di<a[j] && j>=0){
      a[j+1]=a[j];            m++ ;c++;
      j--;
   }
   a[j+1]=di;     m++ ;
 }
  impre(a);
// Cmin= n-1  Mmin= 2(n-1)
// Cmed= 1/4(n**2+n-2)  Mmed= 1/4(n**2+9n-10)
// Cmax= 1/2(n**2+n)-1  Mmax= 1/2(n**2+3n-4)
 
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