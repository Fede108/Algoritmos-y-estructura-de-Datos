#include "../inc/Router.h"
#include "../inc/Tree.h"


void Router ::recibirPagina (Pagina pagina){
    for (int i = 0; i < pagina.tamaño ; i++)
    {
        // dividir pagina en paquetes
        Paquete* paquete = new Paquete();
        paquete->ip = pagina.ip;
        paquete->informacion = pagina.informacion;
        paquete->nroPaquete = i;
        paquetesEnviar->add(paquete);
    }
}

void Router::recibirPaquete(Paquete* paquete){ // recibo paquete del vecino
    paquetesEnviar->add(paquete);   // pierdo un turno antes de enviar el paquete al vecino
}

void Router::enviarCola() // guardo en la cola del vecino correspondiente segun camino optimo
{
    if (paquetesEnviar->esvacia()) return;
    int b = 0;
    int destino = 0;
    destino = tablaRuta[paquetesEnviar->last()->ip];
    
    while (b == 0 && destino>-1)
    {   
        if(tablaRuta[destino] == -1) b = 1;
        else destino = tablaRuta[destino];
    }
    if (destino == -1)
    {
        destino = paquetesEnviar->last()->ip;
    }
    if(destino == n){
        terminal->recibirPagina(paquetesEnviar->last());
        return;
    }  
    vecinos->busca(destino)->paquetes->add(paquetesEnviar->last());
    paquetesEnviar->borrar_last();
}

void Router ::enviarPaquete(){   // envio paquete al vecino
    Paquete *p;
    int destino;
    for (int i = 0; i < K; i++)
    {
        nodo* nodoVecino = vecinos->busca(tablaVecinos[i]); 
        if (nodoVecino->paquetes->esvacia())  return;
        p = nodoVecino->paquetes->tope();
        nodoVecino->paquetes->desencolar();
        nodoVecino->router->recibirPaquete(p);
    }
}  
    
void Router :: agregarNodoAdyacente(Router* router){
    terminal = new Terminal(this);
    vecinos->CreaArbolBus(router);
    tablaVecinos[i++] = router->n;
}

int Router :: tamaño(int n) {
    if (!vecinos->busca(n))
    {
        return 9000;
    }
    return vecinos->busca(n)->paquetes->size();
}

void Router :: imp(){
    vecinos->IRD();
}

void Router :: actualizarTabla(int *tabla){
   // delete tablaRuta;
    tablaRuta = tabla;
}