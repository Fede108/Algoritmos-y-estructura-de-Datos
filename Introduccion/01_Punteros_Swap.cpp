#include <stdio.h>
#include <stdlib.h>

void swap0(int a,int b){
     int w;
     w=b;
     b=a;
     a=w;
}
void swap1(int *a,int *b){
     int w;
     w=*b;
     *b=*a;
     *a=w;
}

void swap2(int *a,int *b){
     int *w;
     printf("en swap2 a:%d - b:%d \n",*a,*b);
     w=b;
     b=a;
     a=w;
     printf("saliendo swap2 a:%d - b:%d \n",*a,*b);
}

int main(int argc, char *argv[])
{
 int x=4;
 int y=5;
 int *xx;
 int *yy;
 
 xx=(int *)malloc(sizeof(int));
 yy=(int *)malloc(sizeof(int));

 
 *xx=14;
 *yy=15;
 printf("antes de swap0 x:%d - y:%d \n",x,y);
 swap0(x,y);
 printf("despues de swap0 x:%d - y:%d \n",x,y);

 printf("antes de swap1 x:%d - y:%d \n",x,y);
 swap1(&x,&y);
 printf("despues de swap1 x:%d - y:%d \n",x,y); 

 printf("antes de swap2 xx:%d - yy:%d \n",*xx,*yy);
 swap2(xx,yy);
 printf("despues de swap2 xx:%d - yy:%d \n",*xx,*yy); 
 system("PAUSE");
 free(xx);
 free(yy);
 return 0;
}
