
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

template <class T> class nodo {
public:
    T info;
    nodo* der, * izq;
};

template <class T> class arbol {
private:
    nodo<T>* raiz, * q;
    void ArbolBusq(T x, nodo<T>*& nuevo);
    void rid(nodo<T>* aux);
    void ird(nodo<T>* aux);
    void idr(nodo<T>* aux);
    void show(nodo<T>* aux, int n);

public:
    arbol() { raiz = NULL; };
    ~arbol() {};
    void CreaArbolBus(T x);
    void RID() { rid(raiz); }
    void IRD() { ird(raiz); }
    void IDR() { idr(raiz); }
    void VerArbol() { show(raiz, 0); }
    void MostrarHojas(nodo<T>* aux); //muestra todas las hojas del arbol
    bool Esta(int x, nodo<T>* aux); //retorna true si x esta en el arbol
    bool esta(int x){ return Esta(x,raiz);}
    T menor(nodo<T>* aux );
    T Menor(){ return menor(raiz);} // retorna el menor valor del arbol
     void borrar(int x, nodo<T>* aux, nodo<T>* Q);
    void Borrar(int x){borrar(x,raiz,q)}; // elimina el nodo que contiene el dato x
};


template <class T> void arbol<T>::CreaArbolBus(T x)
{
    ArbolBusq(x, raiz);
}
template <class T> void arbol<T>::ArbolBusq(T x, nodo<T>*& nuevo)
{
    if (nuevo == NULL) {
        nuevo = new nodo<T>;
        nuevo->info = x; nuevo->der = nuevo->izq = NULL;
    }
    if (x > nuevo->info) ArbolBusq(x, nuevo->der);
    if (x < nuevo->info) ArbolBusq(x, nuevo->izq);
}
template <class T> void arbol<T>::ird(nodo<T>* aux)
{
    if (aux != NULL) {
        ird(aux->izq);
        cout << "\n" << aux->info;
        ird(aux->der);
    }
}
template <class T> void arbol<T>::rid(nodo<T>* aux)
{
    if (aux != NULL) {
        cout << "\n" << aux->info;
        rid(aux->izq);
        rid(aux->der);
    }
}
template <class T> void arbol<T>::idr(nodo<T>* aux)
{
    if (aux != NULL) {
        idr(aux->izq);
        idr(aux->der);
        cout << "\n" << aux->info;
    }
}
template <class T> void arbol<T>::show(nodo<T>* aux, int n)
{
    int i;
    if (aux != NULL) {                      //OjO este es un recorrido dri
        show(aux->der, n + 1);
        for (i = 1; i <= n; i++) cout << "     ";
        cout << aux->info << "\n";
        show(aux->izq, n + 1);
    }
}

template <class T> void arbol<T>::MostrarHojas(nodo<T>* aux){
    if(aux != NULL){
        MostrarHojas(aux->izq);    
        if(aux->der == NULL && aux->izq == NULL){
             cout << aux->info << "\n";
        }
        MostrarHojas(aux->der);
    }
}

template <class T> bool arbol<T>::Esta(int x, nodo<T>* aux){
    if (aux != NULL)
    {
        if(aux->info == x ) return true;
        return Esta(x,aux->der) || Esta(x,aux->izq);;
    }
        return false;
}

template <class T> T arbol<T>:: menor(nodo<T>* aux ){
    if(aux->izq != NULL){
        return menor(aux->izq);    
    }
    return aux->info;    
}

template <class T> void arbol<T> :: borrar(int x,nodo<T>* aux,nodo<T>* Q){
    if (x > aux->info) borrar(x, aux->der,aux->der);
    if (x < aux->info) borrar(x, aux->izq,aux->izq);
    if (aux->der != null){
        if(Q->izq != null){
            borrar(x,aux,Q->der);
            aux->info = Q->der->info;
        }else{
            aux->info = Q->info;
        }   
    }
    

}

//-------------------------------------------------------
int main(int argc, char* argv[])
{
    int i,x;
    arbol<int> A;
    int vec[10] = { 50,12,18,240,222,45,410,325,38,95 };
    //int vec[10]={50,120,180,240,252,450,460,475,488,595};
    for (i = 0; i < 10; i++) {
        A.CreaArbolBus(vec[i]);
        //T.VerArbol();
        //system("PAUSE");
    }

    A.VerArbol();
    
    cout << "\n IRD--------------------------------";
    A.IRD();
    cout << "\n RID--------------------------------";
    A.RID();
    cout<<"\n IDR--------------------------------";
    A.IDR();
   
   
    cout << "\n Mostrar Hojas ----------";
   // A.MostrarHojas();

   
    if (A.esta(45))cout << "\n\n El dato  esta";
    else cout << "\n\n El dato NO esta";

     cout << "\n El menor del arbol= " << A.Menor();

    /*
    
       for(i=0;i<5;i++){
         cout<<"\n -------------------------------- Ing dato a borrar= "; cin>>x;
         A.Borrar(x);
         A.VerArbol();

       }
    */
    cout << endl << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}

/*
Realizar los siguientes metodos de la clase arbol
void MostrarHojas() //muestra todas las hojas del arbol
bool Esta(x) //retorna true si x esta en el arbol
T Menor() // retorna el menor valor del arbol
T Mayor() // retorna el mayor valor del arbol
void Borrar(x) // elimina el nodo que contiene el dato x

*/
