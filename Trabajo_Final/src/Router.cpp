#include "../inc/Router.h"
#include "../inc/Tree.h"
#define INFI 9000
using namespace std;

void Router :: almacenar(Paquete* paquete){
    Lista<Paquete*>* bufferPaquetes = bufferPaginas.get(paquete->pagina->id);
    if(!bufferPaquetes){ bufferPaquetes = new Lista<Paquete*>;
        bufferPaginas.add(paquete->pagina->id, bufferPaquetes);
    } 
    bufferPaquetes->addOrdenado(paquete);
    // si la pagina ya se encuentra completa
    if(bufferPaquetes->size() == paquete->pagina->tamaño){ 
        Paquete* arr = new Paquete[bufferPaquetes->size()];
        int i = 0;
        while (!bufferPaquetes->esvacia())
        {
            arr[i++] = *bufferPaquetes->cabeza();
            bufferPaquetes = bufferPaquetes->resto();
        }
        terminales.get(paquete->pagina->getByteMSB())->recibirPagina(arr);
        delete bufferPaquetes; delete[] arr;
        bufferPaginas.borrar(paquete->pagina->id);
    }
}

void Router::recibirPagina (Pagina* pagina){
    if( pagina->getByteLSB() == ip.to_ulong() ) {          // si la pagina tiene como destino una terminal conectado al router
        terminales.get(pagina->getByteMSB())->recibirPagina(pagina); 
    } 
    else{
        // dividir pagina en paquetes segun su tamaño
        for (int i = 0; i < pagina->tamaño ; i++)   
        {
            Paquete* paquete = new Paquete();
            paquete->nroPaquete = i;
            paquete->pagina = pagina;
            procesarPagina->addLast(paquete); 
        }
    }
}
    
void Router::recibirPaquete(Paquete* paquete){ // recibo paquete del vecino
    if( paquete->pagina->getByteLSB() == ip.to_ulong() ) {      // si el paquete tiene como destino una terminal conectado al router
       almacenar(paquete);
    }
    else{
        procesarVecinos->addLast(paquete);  // pierdo un turno antes de enviar el paquete al vecino
    }       
}

void Router :: recepcion(){
    Vector<nodo*> listaVecinos = vecinos.listar();
    for (int i = 0; i < listaVecinos.size(); i++)
    {
        listaVecinos.get(i)->cantEnviados = 0;          // resetea cantidad de enviados a 0 en el turno
    }
    enviarCola(procesarPagina, procesarVecinos);
}

void Router::enviarCola(Lista<Paquete*> *procesarPagina, Lista<Paquete*> *procesarVecinos) // guardo en la cola del vecino correspondiente segun camino optimo
{   
    int destino;
    Paquete* p;
    nodo* vecino;
    if(procesarPagina->esvacia() && procesarVecinos->esvacia() ) return;
    if(!procesarPagina->esvacia()){
        p = procesarPagina->cabeza();   // buscar el destino e ir agregar a cada cola segun ancho de banda de esa cola 
        destino = calcularDestino(p->pagina->getByteLSB());    // encuentro el camino optimo
        vecino  = vecinos.buscar(destino);
        procesarPagina = procesarPagina->resto();
        if (vecino->cantEnviados < A){    // envio pagina segun ancho banda para intercalar con demas maquinas
            vecino->colaDeEspera->add(p);
            vecino->cantEnviados++;
            this->procesarPagina->borrarDato(p); 
      }   
    }
    if(!procesarVecinos->esvacia()){ 
        p = procesarVecinos->cabeza();   // buscar el destino e ir agregar a cada cola segun ancho de banda de esa cola 
        destino = calcularDestino(p->pagina->getByteLSB());    // encuentro el camino optimo
        vecino  = vecinos.buscar(destino);
        procesarVecinos = procesarVecinos->resto();
        vecino->colaDeEspera->add(p);
        this->procesarVecinos->borrarDato(p); 
    } 
    enviarCola(procesarPagina, procesarVecinos);   // sigo con el resto de los paquetes 
}

int Router::calcularDestino(int destino){
    if(tablaRuta[destino] == -1)
    {
        cout<< "no hay camino "; return 0;
    }
    if(destino == tablaRuta[destino]) return destino;  // si el destino es un vecino directo, retorna el destino 
    destino = tablaRuta[destino]; 
    return calcularDestino(destino);  // recursion hasta encontrar un vecino directo
}

void Router ::enviarPaquete(){   // envio paquete al vecino
    Paquete *p;
    int a = 0;
    Vector<nodo*> listaVecinos = vecinos.listar();
    for (int i = 0; i < listaVecinos.size(); i++)
    {
        while (!listaVecinos.get(i)->colaDeEspera->esvacia() && a<A )   // mientras la cola de espera tenga paquetes y no se llene ancho banda
        {
            p = listaVecinos.get(i)->colaDeEspera->tope();
            listaVecinos.get(i)->colaDeEspera->desencolar();
            listaVecinos.get(i)->router->recibirPaquete(p); 
            a++;
        }
        a = 0;
    }
}  
    
void Router :: agregarNodoAdyacente(Router* router){
    vecinos.agregarNodo(router);
}

int Router :: tamañoCola(int n) {
    if (!vecinos.buscar(n))
    {
        return INFI;
    }
    return vecinos.buscar(n)->colaDeEspera->size(); 
}

void Router :: impre(){
    vecinos.IRD();
}