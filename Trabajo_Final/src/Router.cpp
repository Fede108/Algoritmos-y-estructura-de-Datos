#include "../inc/Router.h"

nodo::nodo(Router* router) : router(router)
{
    paquetes = new Cola<int>();
}
nodo::~nodo()
{
    delete paquetes;
}

void Router::agregarNodoAdyacente(Router* router){
    nodo* n = new nodo(router);
    vecinos->add(n);
}

int Router :: tamaño(Lista<nodo*>* adyacentes, int n) {
    if(!adyacentes->esvacia()){
        if(n == adyacentes->cabeza()->router->n) return adyacentes->cabeza()->paquetes->size();
        return tamaño(adyacentes->resto(), n);
    }
    return 9000;
}

void Router :: imp(Lista<nodo*>* adyacentes){
    while(!adyacentes->esvacia()){
         cout<< adyacentes->cabeza()->router->n <<"  "<<adyacentes->cabeza()->paquetes<<"  ";
         adyacentes = adyacentes->resto();
    }
}

void Router :: actualizarTabla(int *tabla){
    delete tablaRuta;
    tablaRuta = tabla;
    for (int i = 0; i < 10; i++)
    {
        cout << tablaRuta[i] ;
    }
     cout << endl;
    
}