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
    this->paquete = paquete;  // pierdo un turno antes de enviar el paquete al vecino
}

void Router::enviarCola() // guardo en la cola del vecino correspondiente segun camino optimo
{   
    static int turno = 0;
    Paquete* p = new Paquete();
    if (paquetesEnviar->esvacia() && paquete == NULL) return; 
    if (paquetesEnviar->esvacia()){
        p = paquete;
        paquete = NULL;
    }
    else if (paquete == NULL) {
        p = paquetesEnviar->last();
        paquetesEnviar->borrar_last();
    }
    else{  p = (turno) ? paquete : paquetesEnviar->last() ;
           if (turno) paquetesEnviar->borrar_last(); 
           else paquete = NULL;
    }
    turno = (turno%2) ? 0 : 1;

    int b = 0;
    int destino = 0;
    destino = tablaRuta[p->ip];
    
    while (b == 0 && destino>-1)
    {   
        if(tablaRuta[destino] == -1) b = 1;
        else destino = tablaRuta[destino];
    }
    if (destino == -1)
    {
        destino = p->ip;
    }
    if(destino == n){
        terminal->recibirPagina(p);
        return;
    }  
    vecinos->busca(destino)->paquetes->add(p);
}

void Router ::enviarPaquete(){   // envio paquete al vecino
    Paquete *p;
    int destino;
    for (int i = 0; i < K; i++)
    {
        nodo* nodoVecino = vecinos->busca(tablaVecinos[i]); 
        if (nodoVecino->paquetes->esvacia()) {   }
        else{ p = nodoVecino->paquetes->tope();
        nodoVecino->paquetes->desencolar();
        nodoVecino->router->recibirPaquete(p); }
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