//  Pila con Arreglo.cpp  
//

#include <cstdlib>
#include <iostream>
#include <sstream>

#define MAX 100
using namespace std;

// Pila arreglo con estructura estatica

template <class T> class Pila {
private:
    T d[MAX];
    int p;
public:
    Pila() { p = -1; };
    void apilar(T x) { d[++p] = x; };
    T tope(void) { return d[p]; };
    void desapilar(void) { p--; };
    bool pilavacia() { return p == -1; };
};



int main()
{
    /*
    Pila<string>* p = new Pila<string>();
    p->apilar("10");  p->apilar("11");
    p->apilar("12");  p->apilar("13");
    if (!p->pilavacia()) cout << p->tope() << endl;
    if (!p->pilavacia())p->desapilar();
    if (!p->pilavacia())cout << p->tope() << endl;
    if (!p->pilavacia())p->desapilar();
    if (!p->pilavacia())cout << p->tope() << endl;
    */








    
    string cadena;
    Pila<char>* p = new Pila<char>();
    cout << endl << "Ingrese cadena= "; cin >> cadena;
    int error = false;
    for (int i = 0; (i < cadena.length()) && (!error); i++) {
        if (cadena.at(i) == '{') p->apilar('{');
        if (cadena.at(i) == '[') p->apilar('[');
        if (cadena.at(i) == '(') p->apilar('(');

        if (cadena.at(i) == '}') {
            if (p->pilavacia()) error = true;
            else
                if (p->tope() != '{') error = true;
                else p->desapilar();
        }
        if (cadena.at(i) == ']') {
            if (p->pilavacia()) error = true;
            else
                if (p->tope() != '[') error = true;
                else p->desapilar();
        }
        if (cadena.at(i) == ')') {
            if (p->pilavacia()) error = true;
            else
                if (p->tope() != '(') error = true;
                else p->desapilar();
        }
    }//fin for i
    if ((!error) && p->pilavacia())cout << endl << "TOdo OK";
    else cout << endl << "ERROR";
    


    cout << endl << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}
