#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

template <class T> class Pila{
        private:
                T *ptr;
                int capacidad;
        public:
             Pila(){ capacidad=0; ptr = nullptr;};
             void apilar(T d){add(d);};
             void desapilar(void){borrar();};
             T tope(void){return this->cabeza();};
             bool pilavacia(){return this->esvacia();};

             void add(T d); //sumar elementos al arreglo
             bool esvacia(void);
             T cabeza(void); //retorna el dato del primer elemento del arreglo
             void borrar(void); //borra la cabeza
};     

template <class T> void Pila<T> :: add(T d){
    capacidad++;
    T *arreglo = new T[capacidad];
    for (int i = 1; i < capacidad ; i++)
    {
        arreglo[i] = *ptr;
        ptr++;
    }
    ptr = arreglo;
    arreglo[0] = d; 
}

template <class T> void Pila<T> :: borrar(){ /*  el sistema de memoria necesita la referencia 
                                                exacta al inicio del bloque para liberar correctamente 
                                                la memoria asignada con new[].*/
    if (esvacia()) return ;  
    capacidad--;
    if (capacidad == 0)
    {
        ptr = nullptr;
    }else {
        T *arreglo = new T[capacidad];
        for (int i = 0; i < capacidad; i++)
        {
            arreglo[i] = *(ptr + 1 + i);
        }  
        delete[] ptr;
        ptr = arreglo;
    }
}

template <class T> T Pila<T> ::cabeza(){
    return *ptr;
}

template <class T> bool Pila<T> :: esvacia(){
  return ptr == nullptr; 
}

int main()
{
  /*Pila<string> *p= new Pila<string>();
  p->apilar("10");  p->apilar("11");
  p->apilar("12");  p->apilar("13");
  if (!p->pilavacia()) cout<<p->tope()<<endl;
  if (!p->pilavacia())p->desapilar();
  if (!p->pilavacia())cout<<p->tope()<<endl;
  if (!p->pilavacia())p->desapilar();
  if (!p->pilavacia())cout<<p->tope()<<endl;*/

  Pila<char> *p = new Pila<char>();
  string cadena;
  cout<<endl<<"Ingrese cadena= "; cin>>cadena;
  int error=0;
  int cont = 0;
  for(int i=0;i<cadena.length();i++){
          cout<<cadena.at(i)<<endl;
          if (cadena.at(i) == '(' || cadena.at(i) == '{' || cadena.at(i) == '[')
          {
            p->apilar(cadena.at(i));
            cont++;
          }
          switch (cadena.at(i))
          {
          case ')' :   
            if( ! p->esvacia()){
                if(p->tope() != '(') error = 1; 
                p->desapilar();
            }
            cont--;
            break;
         case '}' :
            if( ! p->esvacia()){
                if(p->tope() != '{') error = 1; 
                p->desapilar();
            }
            cont--;
         case ']' :
            if( ! p->esvacia()){
                if(p->tope() != '[') error = 1; 
                p->desapilar();
            }
            cont--;
          default:
            break;
          }
  }
    error = (cont == 0) ? error : 1;
    cout << error << endl;
    cout << cont << endl;
    system("PAUSE");
    return EXIT_SUCCESS;

}