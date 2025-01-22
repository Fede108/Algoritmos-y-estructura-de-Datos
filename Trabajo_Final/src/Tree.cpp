#include "../inc/Tree.h"
#include "../inc/Router.h"

nodo::nodo(Router* router) : router(router)
{
    colaDeEspera = new Cola<Paquete*>();
}
nodo::~nodo()
{
    delete colaDeEspera;
}

//---------------------------------------------------------------------------------------------------------

void arbol :: recorridoTransversal(nodo* n, Vector<nodo*> *r ){  // recorrido postorden idr
     if(n != NULL){
        recorridoTransversal(n->izq, r);
        recorridoTransversal(n ->der, r);
        r->push(n);
    }
}

void arbol:: ird(nodo *aux)
{
    if (aux != NULL) {
        ird(aux->izq);
        cout<<" -> "<<aux->router->n;
        ird(aux->der);
    }
}

void arbol::agregarNodo(Router* router)
{
    ArbolBusq(router, raiz);
}
 
void arbol::ArbolBusq(Router* router, nodo*& nuevo)
{
    if (nuevo == NULL) {
        nuevo = new nodo(router);
        nuevo->der = nuevo->izq = NULL;
        return;
    }
    if (router->n.to_ulong() > nuevo->router->n.to_ulong()) ArbolBusq(router, nuevo->der);
    if (router->n.to_ulong() < nuevo->router->n.to_ulong()) ArbolBusq(router, nuevo->izq);
}

nodo* arbol::busca(nodo* aux, unsigned long x)
{
    if (aux == NULL) return NULL;
    else if (x == aux->router->n.to_ulong()) return aux;
    else if (x > aux->router->n.to_ulong())  return busca(aux->der, x);
    else if (x < aux->router->n.to_ulong())  return busca(aux->izq, x);
    return aux;
}
