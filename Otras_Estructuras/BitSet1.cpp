
#include <iostream>
#include <string>
#include <bitset>
using namespace std;

int main ()
{ bitset<10> a; // crea a con todos ceros

  bitset<10> b(0xAA); // crea b con 10101010

  bitset<10> c(string("01011")); // crea c con 01011
  
  cout<< a<<endl;
  cout<< b<<endl;
  cout<< c<<endl;
  cout<<"----------------------"<<endl;
  a.set(2); //pone en 1 el bit 2
  a[5]=1;   //pone en 1 el bit 5
  cout<< a<<endl;
  
  b.set(); // pone todo en 1
  cout<< b<<endl;
  a.reset(); // pone todo en 0
  cout<< a<<endl;

  
  cout<<"----------------------"<<endl;
  cout<< c<<endl;
  cout<<c.test(2)<<endl; // test retorna 1 o 0
  cout<<c.size()<<endl; // cantidad de bits del objeto
  cout<<c.count()<<endl; //cantidad de unos
  cout<<c.any()<<endl;   //retorna 1 si hay algun 1
  cout<<c.none()<<endl;  //retorna 1 si todos 0
  cout<<"----------------------"<<endl; 
  a=0xAF;
  b=0xAA;
  cout<< a<<endl;
  cout<< b<<endl;
  cout << (a|b) << endl;          // OR Union
  cout << (a&b) << endl;          // AND Interseccion
  cout << (a^b) << endl;          // XOR
  cout<<"----------------------"<<endl; 
  cout<< a<<endl;
  cout << (a<<=5) << endl;              // dos lugares izq
  cout << (a>>=5) << endl;              // un lugar der

 
   
  cout<<endl<<endl;
  system("PAUSE");
  return 0;
}