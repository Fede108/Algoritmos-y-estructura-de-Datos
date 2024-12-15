#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

#define MAX 2
template <class T> class Cola  {
private:
    int cola[MAX];
    int p1;
    int p2;
public:
    Cola(void) { p1 = 0; p2=0; };
    //~Cola(void);
    T tope() { return cola[p2];  };
    bool colallena(void) { return (p1 + 1 == p2) || ((p1 == MAX) && p2 == 0);};
    bool colavacia(void) { return p1 == p2 ;};
    void encolar(T a) { if( !colallena()){
                        p1 = (p1 == MAX) ? 0 : p1;
                        cola[p1++] = a; }
    };
    void desencolar(void) { if(!colavacia()) p2 = (p2 == MAX) ? 0 : p2 + 1; };
    T ultimo(void) { return cola[p2]; };
    string imprimir(string s) { return this->toPrint(s,this); };
    string toPrint(string p, Cola* col);
};


template <class T>
string Cola<T>::toPrint(string p, Cola* col)
{   
    Cola *c1 = new Cola();
    *c1 = *col;
    if (c1->colavacia()) {
        return p;
    }
    else {
        //std::ostringstream stm;
        ostringstream stm;
        c1->desencolar();
        stm << col->tope() << "-" << toPrint(p,c1) << endl;
        //cout<<endl<<" stm.str()= "<<stm.str()<<endl;
        return stm.str();
    }
  //  delete c1;
}

int main()
{
    Cola<int>* c = new Cola<int>();
    if (c->colavacia()) cout << endl << "La cola esta VACIA" << endl << endl;
    c->encolar(15);
    c->encolar(2);
    c->encolar(3);
    cout << c->imprimir(" >>>") << endl;
    cout << "en cola:" << c->tope() << endl;
    cout << "ultimo ingresado= " << c->ultimo() << endl;
    if (!c->colavacia())c->desencolar();

    if (!c->colavacia()) cout << "en cola:" << c->tope() << endl;
    if (!c->colavacia())cout << c->imprimir(" >>>") << endl;
    if (!c->colavacia())c->desencolar();

    cout << "en cola:" << c->tope() << endl;
    cout << c->imprimir(" >>>") << endl;
    if (!c->colavacia())c->desencolar();
    cout << "en cola:" << c->tope() << endl;
    cout << c->imprimir(" >>>") << endl;

    c->encolar(44);
    cout << "en cola:" << c->tope() << endl;
    cout << c->imprimir(" >>>") << endl;
    if (!c->colavacia())c->desencolar();
    cout << c->imprimir(" >>>") << endl;


    cout << endl << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}