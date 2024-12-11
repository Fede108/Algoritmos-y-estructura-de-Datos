#include <cstdlib>
#include <iostream>

using namespace std;

void impre(int v[],int n);
int suma(int v[],int n);
int mayor(int v[],int n);
int multi(int,int);
void hanoi(char a,char c, char b, int n);

int main(int argc, char *argv[])
{   
    int v[6]={17,15,-8,30,5,-2};
    char nom[]={"Juan Perez"};
    
	cout<<"impre vector"<<endl; impre(v,5);    
    cout<<"impre suma "<< suma(v,5) <<endl;    
    cout<<"mayor vec " << mayor(v,5) <<endl;
    cout<<"multi "<<multi(8,7)<<endl;
   
        system("PAUSE");
    return EXIT_SUCCESS;
}

void impre(int v[],int n) // puntero a un arreglo -> es lo mismo que impre(int *v, int n) puntero 
{   if(n==0)cout<<v[n]<<endl;
    else{ 
          //cout<<"estoy yendo";
          //cout<<v[n]<<endl;
          impre(v,n-1);
          //cout<<"estoy retornando"<<endl;
          cout<<v[n]<<endl;          
    } 
}

int suma(int v[], int n){
    if(n==0) return v[n];
    return suma(v,n-1) + v[n];
}

int mayor(int v[], int n){
    int m = 0;
    if(n==0) return v[n];
    m = mayor(v,n-1);
    return ( m > v[n] ) ? m : v[n];
}

int multi(int a, int b){
    if (b==1) return a;
    return a + multi(a,b-1);
}


void hanoi(char a,char c, char b, int n){
    if(n>0){
             hanoi(a,b,c,n-1);
cout<<"Mover "<<n<<" desde "<<a<<" hasta "<<c<<endl;
             hanoi(b,c,a,n-1);
     }
}

    