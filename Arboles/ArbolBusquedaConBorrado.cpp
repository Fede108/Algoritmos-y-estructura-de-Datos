
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

    void borrar(nodo<T>*& p, T x);
    void bor(nodo<T>*& d);
    void mh(nodo<T>* aux);
    T menor(nodo<T>* aux);
    bool esta(nodo<T>* aux, T x);

public:
    arbol() { raiz = NULL; };
    ~arbol() {};
    void CreaArbolBus(T x);
    void RID() { rid(raiz); }
    void IRD() { ird(raiz); }
    void IDR() { idr(raiz); }
    void VerArbol() { show(raiz, 0); }

    void Borrar(T x) { borrar(raiz, x); }
    void MostrarHojas() { mh(raiz); }
    T Menor() { return menor(raiz); }
    bool Esta(T x) { return esta(raiz, x); }
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

    A.IRD();
    cout << "\n--------------------------------";
    /*A.RID();
    cout<<"\n--------------------------------";
    A.IDR();
   */
    cout << "\n Mostrar Hojas ----------";
    A.MostrarHojas();

    cout << "\n El menor del arbol= " << A.Menor();

    if (A.Esta(95))cout << "\n\n El dato 95 esta";
    else cout << "\n\n El dato 95 NO esta";

    
       for(i=0;i<5;i++){
         cout<<"\n -------------------------------- Ing dato a borrar= "; cin>>x;
         A.Borrar(x);
         A.VerArbol();

       }
    
    cout << endl << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}



template <class T> bool arbol<T>::esta(nodo<T>* aux, T x)
{
    if (aux == NULL) return false;
    else if (x > aux->info) return esta(aux->der, x);
    else if (x < aux->info) return esta(aux->izq, x);
    return true;

}



template <class T> void arbol<T>::mh(nodo<T>* aux)
{
    if (aux != NULL) {
        mh(aux->izq);
        if (aux->izq == NULL && aux->der == NULL)cout << "\n" << aux->info;
        mh(aux->der);
    }
}



template <class T> T arbol<T>::menor(nodo<T>* aux)
{
    if (aux->izq == NULL)return aux->info;
    return menor(aux->izq);
}


template <class T> void arbol<T>::borrar(nodo<T>*& p, T x)
{
    if (p == NULL) cout << "\n El dato NO esta\n\n";
    else if (x > p->info) borrar(p->der, x);
    else if (x < p->info) borrar(p->izq, x);
    else {// lo encontre en el nodo p
        q = p;
        if (q->der == NULL) p = q->izq;// raiz<=raiz del subarbol izq
        else if (q->izq == NULL) p = q->der;//raiz<=raiz del subarbol der
        else bor(q->izq);//busca en el sub arbol izq
        delete q; //elimina nodo
    }
}
template <class T> void arbol<T>::bor(nodo<T>*& d)
{
    if (d->der != NULL) bor(d->der);//busca el elemento mas a la derecha
    else {
        q->info = d->info; // realizo intercambio
        q = d; // apunta al nodo a eliminar (nodo reemplaza al seleccionado)
        d = d->izq; // d izq (si existe) toma lugar de d , nodo der es nulo
    }
}


