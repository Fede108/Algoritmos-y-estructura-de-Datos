// Listas_01.cpp 
//
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

template <class T> class Nodo {
private:
    T dato;
    Nodo* next;
public:
    Nodo() { next = NULL; };
    Nodo(T a) { dato = a; next = NULL; };
    void set_dato(T a) { dato = a; };
    void set_next(Nodo* n) { next = n; };
    T get_dato() { return dato; };
    Nodo* get_next() { return next; };
    bool es_vacio() { return next == NULL; }
};

template <class T> class Lista {
private: Nodo<T>* czo;
public:
    Lista() { czo = new Nodo<T>(); };
    Lista(Nodo<T>* n) { czo = n; };
    //~Lista(void);
    void add(T d);
    bool esvacia(void);
    T cabeza(void);
    Lista* resto(void);
    string toPrint(string p);
    T suma(T i);
    int size(); //cantidad de nodos de la lista
    void borrar(void); //borra la cabeza
    void borrar_last(); //borra el ultimo
    void concat(Lista* l1); // le transfiere los datos de l1 a this
    Lista* copy(void); // hace una copia de la lista
    void tomar(int n); //deja "vivos" los n primeros nodos y borra el resto
};
template <class T>
void Lista<T>::add(T d)
{
    Nodo<T>* nuevo = new Nodo<T>(d);
    nuevo->set_next(czo);
    czo = nuevo;
}
template <class T>
bool Lista<T>::esvacia(void)
{
    return czo->es_vacio();
}
template <class T>
T Lista<T>::cabeza(void)
{
    if (esvacia()) {
        cout << " Error, Cabeza de lista vacia";
        return NULL;
    }
    return czo->get_dato();
}

template <class T>
Lista<T>* Lista<T>::resto(void)
{
    Lista* l = new Lista(czo->get_next());
    return (l);
}

template <class T>
string Lista<T>::toPrint(string p)
{
    if (this->esvacia()) {
        return p;
    }
    else {
        //std::ostringstream stm;
        ostringstream stm;
        stm << this->cabeza() << "-" << this->resto()->toPrint(p) << endl;
        //cout<<endl<<" stm.str()= "<<stm.str()<<endl;
        return stm.str();
    }
}

template <class T>
T Lista<T>::suma(T i)
{    //cout<<" i al entrar= "<<i<<endl;
    if (this->esvacia()) {
        return i;
    }
    else {

        //cout<<"this->cabeza()= "<<this->cabeza()<<endl;   
        return this->resto()->suma(i + this->cabeza());
    }
}

template <class T> int Lista<T> :: size(){
    if(esvacia()){
        return 0;
    } else{
                 
        return 1+this->resto()->size();
    }         
} 

template <class T> void Lista<T> :: borrar(void){ //borra la cabeza
   
    Nodo<T>* n = czo;
    czo = czo->get_next();
    delete n;    
}

template <class T> void Lista<T> :: borrar_last(){ //borra el ultimo
    Nodo<T> *n = czo;
    Nodo<T> *aux;
    while (!n->get_next()->es_vacio()){
        aux = n;
        n = n->get_next();
    }
    aux->set_next(n->get_next());

}

template <class T> void Lista<T> :: concat(Lista* l1){// le transfiere los datos de l1 a this
    if(l1->esvacia()){
        return;
    }
    Lista *aux = l1;
    concat(aux->resto());   
    add(aux->czo->get_dato());
    return;
}

template <class T> Lista<T>* Lista<T> :: copy(void){// hace una copia de la lista
    Lista *l = new Lista();      //nueva lista
    Lista *aux = new Lista(czo); //iterador para recorrer lista vieja

    while (!aux->esvacia())
    {
        if (l->esvacia())
        {
            l->add(aux->czo->get_dato());    
        }
        else {
        Lista *n = new Lista();
        n->add(aux->czo->get_dato());
        n->concat(l);
        l = n;        
        }
        aux = aux->resto();
    }
    return l;   
}



template <class T> void Lista<T> :: tomar(int n){//deja "vivos" los n primeros nodos y borra el resto
    if(size(0) < n) return;
    Nodo<T> *aux = czo;
    while (n != 1)
    {
        aux = aux->get_next();
        n--;
    }
    Lista *l = new Lista(czo);
    while (!l->esvacia())
    {
        l = l->resto();
    }
    aux->set_next(l->czo);

}

int main()
{
    Lista<string>* l = new Lista<string>();
    Lista<int>* r = new Lista<int>();
    Lista<string>* l2 = new Lista<string>();
    l->add(" 11x");
    l->add(" 22y");
    l->add(" 33z");
    r->add(100);
    r->add(22);
    cout << "l= "<<l->toPrint("fin") << endl;
    cout << "r= " << r->toPrint("fin") << endl;
    cout << "suma:" << r->suma(0) << endl;
  /*  r->borrar_last();
    cout << "size" << r->size(0)<<endl;

    Lista<int>* f = new Lista<int>();
    f->add(5);
    f->add(8);
    r->concat(f);
    r->copy();
    cout << "size" << r->size(0)<<endl;
    r->tomar(2); */

    cout << "size l= " << l->size() << endl;
    cout << "size r= " << r->size() << endl;
    cout << "size l2= " << l2->size() << endl<<endl;

    l2->add(" AA");
    l2->add(" BB");
    cout << l->toPrint(" soy l")<<endl;
    l2->concat(l);
    cout << l2->toPrint(" soy l2 concatenada con l") <<endl;
    cout << l->toPrint(" soy l")<<endl;
    Lista<string>* copia = l->copy();
    cout << copia->toPrint(" soy copia de l")<<endl;
    l->borrar_last();
    cout << l->toPrint(" soy l")<<endl;
    l->borrar_last();
    cout << l->toPrint(" soy l")<<endl;
    l = copia->copy();
    cout << l->toPrint(" soy l")<<endl;
    l->borrar();
    cout << l->toPrint(" soy l")<<endl;
    cout << l2->toPrint(" soy l2")<<endl;
    l2->tomar(4);
    cout << l2->toPrint(" soy l2")<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;

}


/*
int size();// cantidad de nodos de la lista
void borrar(void); //borra la cabeza
void borrar_last();//borra el ultimo
void concat(Lista* l1);// le transfiere los datos de l1 a this
Lista* copy(void);// hace una copia de la lista
void tomar(int n);//deja "vivos" los n primeros nodos y borra el resto
*/