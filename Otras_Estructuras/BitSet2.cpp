#include <iostream>
#include <string>
#include <bitset>
using namespace std;
class xx{
      public:
      bitset<7> M[7];
      void impre();
      //definiendo and de conjuntos
      friend xx operator &(xx c1, xx c2);
      // definiendo or de conjuntos
      friend xx operator |(xx c1, xx c2); //operador or de conjunto
      int contar(); // cuenta los 1
      friend xx operator <<(xx c1,int n); //shift a la izquierda
      friend bool operator ==(xx c1,xx c2);// compara si son iguales
};

xx operator &(xx c1, xx c2){ 
     xx c3;
     for(int i=0;i<7;i++)
            c3.M[i] = c1.M[i]&c2.M[i];
     return c3;
}
void xx::impre(){
     int i,j;
     for(i=0;i<7;i++){
                      cout<<endl;
                      for(j=6;j>=0;j--)                 
                          cout<<this->M[i][j]<<"  ";
     }
     cout<<endl;
}
                     
int main ()
{  xx a,b,c;
   cout<<"a==b "<<(a==b)<<endl;
   a.M[0][3]=1; a.M[1][2]=1;
   cout<<"a==b "<<(a==b)<<endl;
   cout<<"a.contar="<<a.contar()<<endl;
   a.impre();
   cout<<"----------------------"<<endl;
   b=a;
   b.impre();
   
   b.M[1].set(); b.M[3].set();
   b.M[0].reset();
   cout<<"b.contar="<<b.contar()<<endl;
   b.impre();
   c=a&b;
   c.impre();
   c=a|b;
   c.impre();
   c=c<<2;
   c.impre();
   //b.impre();
   //cout<<endl;
   //c.impre();
   
  cout<<endl<<endl;
  system("PAUSE");
  return 0;
}


int xx::contar(){
    int c=0;
    for(int i=0;i<7;i++)
            c=c+M[i].count();
    return c;
}
            
xx operator |(xx c1, xx c2){
     xx c3;
     for(int i=0;i<7;i++)
            c3.M[i]= c1.M[i]|c2.M[i];
     return c3;
}
            
xx operator <<(xx c1, int n){
     for(int i=0;i<7;i++)
            c1.M[i]<<=n;
     return c1;
}
  
bool operator ==(xx c1, xx c2){
	for(int i=0;i<7;i++){
		for(int j=0;j<7;j++){
			if (c1.M[i][j]!=c2.M[i][j])
				return false;
		}

	}
    return true;
}     