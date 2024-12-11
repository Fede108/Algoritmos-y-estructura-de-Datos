#include <cstdlib>
#include <iostream>

using namespace std;
int suma(int v[],int n);
int mayor(int v[],int n);
int multi(int a,int b);
void impre(int v[],int n);
void hanoi(char a,char c, char b, int n);
void impreD(char *p);

int main(int argc, char *argv[])
{   int v[6]={17,15,-8,30,5,-2};
    char nom[]={"Juan Perez"};
    impreD(nom);
    /*cout<<"impre vector"<<endl; impre(v,5);    
   
    cout<<"suma vec="<<suma(v,5)<<endl;    
    cout<<"mayor vec="<<mayor(v,5)<<endl;    
    cout<<"multiplica 5*7= "<<multi(5,7);
    
    
    cout<<"--------------------------------"<<endl;
    */
    hanoi('a','c','b',5);
    cout<<endl;
    
    system("PAUSE");
    return EXIT_SUCCESS;
}

void impre(int v[],int n)
{   if(n==0)cout<<v[n]<<endl;
    else{ 
          //cout<<"estoy yendo";
          //cout<<v[n]<<endl;
          impre(v,n-1);
          //cout<<"estoy retornando"<<endl;
          //cout<<v[n]<<endl;
          
          
    } 
}

void impreD(char *p)
{ if(*p!='\0'){
               cout<<*p<<endl;
               impreD(p+1);
               //cout<<*p<<endl;
  }
}

int suma(int v[],int n)
{   if(n==0)return v[n];
    else{
         //int s=suma(v,n-1);
         //s=s+v[n];
         //return s;
         return v[n]+suma(v,n-1);     
    }
    //return v[n]+suma(v,n-1);
}

int mayor(int v[],int n)
{   
    if(n==0)return v[n];
    
    int may=mayor(v,n-1);
    return(v[n]>may)?v[n]:may;
    //if (v[n]>may) return v[n];
    //return may;

}

int multi(int a,int b)
{   if(b==0) return 0;
    else return a+multi(a,b-1);
}

void hanoi(char a,char c, char b, int n)
{    if(n>0){
             hanoi(a,b,c,n-1);
cout<<"Mover "<<n<<" desde "<<a<<" hasta "<<c<<endl;
             hanoi(b,c,a,n-1);
     }
     
}











