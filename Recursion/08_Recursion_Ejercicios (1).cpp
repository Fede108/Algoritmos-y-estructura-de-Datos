#include <cstdlib>
#include <iostream>

using namespace std;
// Implementar
int suma(int v[],int n);
int mayor(int v[],int n);
int multi(int a,int b);
void impre(int v[],int n);
void hanoi(char a,char c, char b, int n);
void impreD(char *p);

int main(int argc, char *argv[])
{   s
    int v[6]={17,15,-8,30,5,-2};
    
    cout<<endl;
    
    system("PAUSE");
    return EXIT_SUCCESS;
}

void impre(int v[],int n)
{   
    if(n==0)cout<<v[n]<<endl;
    else{ 
          //cout<<"estoy yendo";
          //cout<<v[n]<<endl;
          impre(v,n-1);
          //cout<<"estoy retornando"<<endl;
          //cout<<v[n]<<endl;
          
          
    } 
}











