// Metodo de Ordenamiento por Intercambio Directo (Burbuja)
// Wirth pag. 71
#include <stdio.h>
#include <stdlib.h>
#define MAX 5000

void impre(int *v);

int main(int argc, char *argv[])
{int i,j,y,pos,aux,b,m=0,c=0;
 int a[MAX];//={50,40,30,20,10}; //
 for(i=0;i<MAX;i++){
                    a[i]=int(rand());
 }
 impre(a);
 puts("\n---------------------------------");
 i=0; b=1;y=0;
 //for(i=0;i<MAX;i++){
 while(b==1){ 
    b=0;
    // pasadas
             
      for(j=y;j<MAX-i;j++){
          c++;               
          if(a[j]>a[j+1]){
              aux=a[j]; a[j]=a[j+1]; a[j+1]=aux; m=m+3;
              b=1;
          }                   
        }
      i++;
  
      for(j=MAX-i;j>y;j--){
          c++;               
          if(a[j]<a[j-1]){
              aux=a[j-1]; a[j-1]=a[j]; a[j]=aux; m=m+3;
              b=1;
          }                   
      }
      y++;
    
    
 }
  impre(a);
// ---------       Mmin= 0
// C= 1/2(n**2-n)  Mmed= 3/4(n**2-n)
// --------------  Mmax= 3/2(n**2-n)
   
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