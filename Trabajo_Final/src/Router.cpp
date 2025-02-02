#include "../inc/Router.h"
#include "../inc/Tree.h"
#define INFI 9000
using namespace std;

void Router :: almacenar(Paquete* paquete){
    Lista<Paquete>* bufferPaquetes = bufferPaginas.get(paquete->pagina->id);
    if(!bufferPaquetes)
    { 
        bufferPaquetes = new Lista<Paquete>;
        bufferPaginas.add(paquete->pagina->id, bufferPaquetes);
    } 
    bufferPaquetes->addOrdenado(*paquete); 
    Pagina* pagina = paquete->pagina;
    delete paquete;
    
    if(bufferPaquetes->size() == pagina->tamaño)   // si la pagina ya se encuentra completa
    { 
        Paquete *arr = new Paquete[pagina->tamaño]; int i = 0;
        while (!bufferPaquetes->esvacia()){
                arr[i++] = bufferPaquetes->cabeza();
                bufferPaquetes->borrar();
        }
        pagina->paquetes = arr;
        terminales.get(pagina->getTermDestino())->recibirPagina(pagina);
        bufferPaginas.borrar(pagina->id);
        delete bufferPaquetes;
    }
}

void Router::recibirPagina (Pagina* pagina){
    if( pagina->getRoutDestino() == this->ip) // si la pagina tiene como destino una terminal conectado al router
    {    
        terminales.get(pagina->getTermDestino())->recibirPagina(pagina); 
    } 
    else if( calcularDestino(pagina->getRoutDestino()) == INFI )
    {
        // no se envia la pagina
         cout<< " ¡NO HAY RUTA! No se puede enviar\n ";
    } 
    else{
        for (int i = 0; i < pagina->tamaño ; i++)   // dividir pagina en paquetes segun su tamaño
        {
            Paquete* paquete = new Paquete();
            paquete->nroPaquete = i;
            paquete->pagina = pagina;
            procesarPagina.addLast(paquete); // pierdo un ciclo antes de enviar el paquete al vecino
        }
    }
}
    
void Router::recibirPaquete(Paquete* paquete){ // recibo paquete del vecino
    if( paquete->pagina->getRoutDestino() == this->ip )   // si el paquete tiene como destino una terminal conectado al router
    {  
       almacenar(paquete);
    }
    else
    {
        procesarVecinos.addLast(paquete);  // pierdo un ciclo antes de enviar el paquete al vecino
    }           
}

void Router :: procesamiento(){
    enviarColaEspera(&procesarPagina, &procesarVecinos);
}

void Router::enviarColaEspera(Lista<Paquete*> *procesarPagina, Lista<Paquete*> *procesarVecinos) // guardo en la cola del vecino correspondiente segun camino optimo
{   
    bool impreso = true;
    while( !procesarPagina->esvacia() || !procesarVecinos->esvacia() ){
        if(impreso){ cout << "\n"; impreso=false;}
        if(!procesarPagina->esvacia())
        {   
            Paquete* p = procesarPagina->cabeza(); 
            procesarPagina = procesarPagina->resto();   // sigo con el resto de los paquetes

            if(procesarPaquete(p, procesarVecinos->esvacia()))  // buscar el destino e ir agregar a cada cola segun ancho de banda
             this->procesarPagina.borrarDato(p);  

        }
        if(!procesarVecinos->esvacia())
        {   
            Paquete* p = procesarVecinos->cabeza(); 
            procesarVecinos = procesarVecinos->resto(); // sigo con el resto de los paquetes 
             
            if(procesarPaquete(p, false))
             this->procesarVecinos.borrarDato(p);  // envia a la cola de espera del vecino correspondiente
        } 
    }
}

bool Router::procesarPaquete(Paquete* p, bool pagCliente ){
    int destino   = calcularDestino(p->pagina->getRoutDestino());    // encuentro el camino optimo
    nodo* vecino  = vecinos.buscar(calcularDestino(p->pagina->getRoutDestino()));
    if(pagCliente)
    {
        if (vecino->paqPagRecibidas++ >= vecino->anchoBanda) return false;    // envio paginas segun ancho banda para intercalar con demas maquinas
    }

    cout << "[Router " << this->ip << "] → [Router " << destino << "] | ";
    imprimirRuta(p);  cout << "\n";

    vecino->encolar(p);
    vecinosEncolados.add(vecino->router->ip, vecino);
    return true;  
}

void Router::reenvio(){   // envio paquete al vecino
    Vector<nodo*> v = vecinosEncolados.listar();
    for (int i = 0; i < v.size(); i++)
    {
        nodo* vecino = v.get(i);
        int paquetesEnviados = 0; 
        while (!vecino->colaDeEspera->esvacia() && paquetesEnviados ++ < vecino->anchoBanda)   // mientras la cola de espera tenga paquetes y no se llene ancho banda
        {   
            Paquete *p = vecino->desencolar();

            cout << " [Router " << vecino->router->ip << "] <- [Router " << this->ip << "] | " << "[ID: " << p->pagina->id << "] Nro: " << p->nroPaquete
                 << " | AnchoBanda: " << paquetesEnviados << "/" << vecino->anchoBanda << " (Faltan: " << vecino->colaDeEspera->size() << ")"
                 << " | Origen: " << p->pagina->getRoutOrigen()<< " | Destino: " << p->pagina->getRoutDestino() << "\n";

            vecino->router->recibirPaquete(p);
            if(vecino->colaDeEspera->esvacia())  vecinosEncolados.borrar(vecino->router->ip);    
        }
        vecino->paqPagRecibidas = 0; // reinicio para el siguiente ciclo
        cout<< "\n";
    }
}  

int Router::calcularDestino(int destino){
    if(tablaRuta[destino] == -1) return INFI;
    if(destino == tablaRuta[destino]) return destino;  // si el destino es un vecino directo, retorna el destino 
    destino = tablaRuta[destino]; 
    return calcularDestino(destino);  // recursion hasta encontrar un vecino directo
}

void Router::imprimirRuta(Paquete* p) {
    cout << " [ID: " << p->pagina->id << "] Nro: " << p->nroPaquete << " | Ruta: " << this->ip;
    int totalCiclos = ruta(p->pagina->getRoutDestino());
    cout << " | Total: "  << totalCiclos << " ciclos" << " | Origen: " <<  p->pagina->getRoutOrigen() << " | Destino: "<< p->pagina->getRoutDestino();
}

int Router::ruta(int destino) {
    int total = vecinos.buscar(calcularDestino(destino))->ciclos;
    if (destino == calcularDestino(destino))  // si el destino es un vecino directo 
    {         
        cout <<  " => " << destino <<" ("<< vecinos.buscar(calcularDestino(destino))->ciclos << ")";  // termina el metodo
        return total;
    }
    cout <<  " => " << calcularDestino(destino) <<" ("<< vecinos.buscar(calcularDestino(destino))->ciclos << ") " << calcularDestino(destino);
    return total + vecinos.buscar(calcularDestino(destino))->router->ruta(destino);   // sigue con el router vecino
}

void Router :: agregarNodoAdyacente(Router* router, int anchoBanda){
    vecinos.agregarNodo(router, anchoBanda);
}

int Router :: tamañoCola(int ip) {
    if (!vecinos.buscar(ip)) return INFI;
    return vecinos.buscar(ip)->colaDeEspera->size(); 
}

int Router :: ciclos(int ip) {
    if (!vecinos.buscar(ip)) return INFI;
    return vecinos.buscar(ip)->ciclos; 
}

void Router :: impre(){
    vecinos.IRD();
}