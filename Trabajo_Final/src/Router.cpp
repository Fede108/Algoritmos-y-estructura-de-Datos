#include "../inc/Router.h"

nodo::nodo(Router* router) : router(router)
{
    paquetes = new Cola<Paquete>();
}
nodo::~nodo()
{
    delete paquetes;
}

void Router ::recibirPagina (Pagina pagina){
    for (int i = 0; i < pagina.tamaño ; i++)
    {
        // dividir pagina en paquetes
        paquete = new Paquete();
        paquete->ip = pagina.ip;
        paquete->informacion = pagina.informacion;
        paquete->nroPaquete = i;
        paquetesEnviar->add(*paquete);
       // enviarCola(vecinos,tablaRuta[paquete->ip]);
    }
}

void Router ::recibirPaquete(Paquete paquete){
    paquetesEnviar->add(paquete);
}

void Router :: enviarCola(Lista<nodo*>* adyacentes, int destino){
    if(!adyacentes->esvacia()){
        if(n == adyacentes->cabeza()->router->n)  adyacentes->cabeza()->paquetes->add(*paquete);
        return enviarCola(adyacentes->resto(), destino);
    }
}

void Router ::enviarPaquete(Lista<nodo*>* adyacentes){
    Paquete p;
    if(!adyacentes->esvacia()){
        if(!adyacentes->cabeza()->paquetes->esvacia()){
            p = adyacentes->cabeza()->paquetes->tope();
            p.ip   // necesito encontrar el vecino con esa ip y enviarle el paquete con vecino.paquete
                    // implementar una estructura para poder usar acceso posicional, simplfica codigo
        }  
    }
}


void Router :: agregarNodoAdyacente(Router* router){
    nodo* n = new nodo(router);
    terminal = new Terminal(router);
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