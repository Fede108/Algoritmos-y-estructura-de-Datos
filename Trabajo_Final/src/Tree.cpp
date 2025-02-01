#include "../inc/Tree.h"
#include "../inc/Router.h"

nodo::nodo(Router* router, int anchoBanda) : router(router), anchoBanda(anchoBanda)
{
    colaDeEspera = new Cola<Paquete*>();
}
nodo::~nodo()
{
    delete colaDeEspera;
}
Paquete* nodo::getTope(){
    Paquete* p = colaDeEspera->tope();
    colaDeEspera->desencolar();
    colaSize = colaDeEspera->size();
    return p;
}

int* nodo::getColaSize(){
    return &colaSize;
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
        cout<<" -> "<<aux->router->ip;
        ird(aux->der);
    }
}

void arbol::agregarNodo(Router* router, int anchoBanda)
{
    ArbolBusq(router, raiz, anchoBanda);
}
 
void arbol::ArbolBusq(Router* router, nodo*& nuevo, int anchoBanda)
{
    if (nuevo == NULL) {
        nuevo = new nodo(router, anchoBanda);
        nuevo->der = nuevo->izq = NULL;
        return;
    }
    if (router->ip > nuevo->router->ip) ArbolBusq(router, nuevo->der, anchoBanda);
    if (router->ip < nuevo->router->ip) ArbolBusq(router, nuevo->izq, anchoBanda);
}

nodo* arbol::busca(nodo* aux, int ip)
{
    if (aux == NULL) return NULL;
    else if (ip == aux->router->ip) return aux;
    else if (ip > aux->router->ip)  return busca(aux->der, ip);
    else if (ip < aux->router->ip)  return busca(aux->izq, ip);
    return aux;
}
