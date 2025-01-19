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
        procesarPagina->addLast(paquete); 
    }
}

void Router::recibirPaquete(Paquete* paquete){ // recibo paquete del vecino
    procesarVecinos->addLast(paquete);  // pierdo un turno antes de enviar el paquete al vecino
}

void Router :: recepcion(){
     for (int i = 0; i < K; i++)
    {
        nodo* nodoVecino = vecinos->buscar(tablaVecinos[i]); 
        nodoVecino->cantEnviados = 0;
    }
    enviarCola(procesarPagina, procesarVecinos);
}

void Router::enviarCola(Lista<Paquete*> *procesarPagina, Lista<Paquete*> *procesarVecinos) // guardo en la cola del vecino correspondiente segun camino optimo
{   
    Paquete* p = new Paquete();
    int destino;
    if(procesarPagina->esvacia() && procesarVecinos->esvacia() ) return;
    if(!procesarPagina->esvacia()){ 
        p = procesarPagina->cabeza();   // buscar el destino y ir agregar a cada cola segun ancho de banda de esa cola 
        if(p->ip == n){ 
            terminal->recibirPagina(p);   
            procesarPagina->borrar();   
        }
        else{
            destino = calcularDestino(p);    // encuentro el camino optimo
            if (vecinos->buscar(destino)->cantEnviados < A){
                vecinos->buscar(destino)->paquetes->add(p);
                vecinos->buscar(destino)->cantEnviados++;
                procesarPagina->borrar();  
            } 
            else {  procesarPagina = procesarPagina->resto(); }             
        } 
    }
    if(!procesarVecinos->esvacia()){ 
        p = procesarVecinos->cabeza();   // buscar el destino y ir agregar a cada cola segun ancho de banda de esa cola 
        if(p->ip == n){ 
            terminal->recibirPagina(p); 
            procesarVecinos->borrar();  
        }
        else{
            destino = calcularDestino(p);
            if (vecinos->buscar(destino)->cantEnviados < A){
                vecinos->buscar(destino)->paquetes->add(p);
                vecinos->buscar(destino)->cantEnviados++;
                procesarVecinos->borrar();  
            }
            else { procesarVecinos = procesarVecinos->resto();  }             
        }
       
    } 
    
    enviarCola(procesarPagina, procesarVecinos);   // sigo con el resto de los paquetes 
}

int Router :: calcularDestino(Paquete* p){
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
    return destino;
}

void Router ::enviarPaquete(){   // envio paquete al vecino
    Paquete *p;
    int destino;
    int a = 0;
    for (int i = 0; i < K; i++)
    {
        nodo* nodoVecino = vecinos->buscar(tablaVecinos[i]); 
        while (!nodoVecino->paquetes->esvacia() && a<A )
        {
            p = nodoVecino->paquetes->tope();
            nodoVecino->paquetes->desencolar();
            nodoVecino->router->recibirPaquete(p); 
            a++;
        }
        a = 0;
    }
}  
    
void Router :: agregarNodoAdyacente(Router* router){
    terminal = new Terminal(this);
    vecinos->CreaArbolBus(router);
    tablaVecinos[i++] = router->n;
}

int Router :: tamaño(int n) {
    if (!vecinos->buscar(n))
    {
        return 9000;
    }
    return vecinos->buscar(n)->paquetes->size() + 1; // se pierde un ciclo al entrar y salir del router
}

void Router :: impre(){
    vecinos->IRD();
}

void Router :: actualizarTabla(int *tabla){
    int* aux = new int[N];
    for (int i = 0; i < N; i++)
    {
        aux[i] = tabla[i];
    }
    delete[] tablaRuta;
    tablaRuta = aux;
}