#include "../inc/Router.h"
#include "../inc/Tree.h"

using namespace std;

void Router :: almacenar(Paquete* paquete){
    Lista<Paquete*>* bufferPaquetes = bufferPaginas.get(paquete->pagina->id);
    if(!bufferPaquetes){
        bufferPaquetes = new Lista<Paquete*>;
        bufferPaginas.add(paquete->pagina->id, bufferPaquetes);
    } 
    bufferPaquetes->addOrdenado(paquete);
   
    if(bufferPaquetes->size() == bufferPaquetes->cabeza()->pagina->tamaño){
        Paquete* arr = new Paquete[bufferPaquetes->size()];
        while (!bufferPaquetes->esvacia())
        {
            for (int i = 0; i < bufferPaquetes->size(); i++)
            {
                arr[i] = *bufferPaquetes->cabeza();
            }
            bufferPaquetes = bufferPaquetes->resto();
        }
        
        terminales.get(paquete->pagina->getByteMSB())->recibirPagina(arr);
        bufferPaginas.borrar(paquete->pagina->id);
    }
}

void Router ::recibirPagina (Pagina* pagina){
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
        // si el paquete tiene como destino una terminal conectado al router
    if( paquete->pagina->getByteLSB() == ip.to_ulong() ) {     
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
    Paquete* p = new Paquete();
    int vecino;
    if(procesarPagina->esvacia() && procesarVecinos->esvacia() ) return;
    if(!procesarPagina->esvacia()){ 
        p = procesarPagina->cabeza();   // buscar el destino e ir agregar a cada cola segun ancho de banda de esa cola 
       
        vecino = calcularDestino(p);    // encuentro el camino optimo
        if (vecinos.buscar(vecino)->cantEnviados < A){
            vecinos.buscar(vecino)->colaDeEspera->add(p);
            vecinos.buscar(vecino)->cantEnviados++;
            procesarPagina->borrar();  
        } 
        else {  procesarPagina = procesarPagina->resto(); }     // sigo con el siguiente paquete a procesar    
        
    }
    if(!procesarVecinos->esvacia()){ 
        p = procesarVecinos->cabeza();   // buscar el destino e ir agregar a cada cola segun ancho de banda de esa cola 

        vecino = calcularDestino(p);
        if (vecinos.buscar(vecino)->cantEnviados < A){
            vecinos.buscar(vecino)->colaDeEspera->add(p);
            vecinos.buscar(vecino)->cantEnviados++;
            procesarVecinos->borrar();  
        }
        else { procesarVecinos = procesarVecinos->resto();  }     // sigo con el siguiente paquete a procesar  
        
    } 
    enviarCola(procesarPagina, procesarVecinos);   // sigo con el resto de los paquetes 
}

int Router :: calcularDestino(Paquete* p){
    int b = 0;
    int destino = 0;
    destino = tablaRuta[p->pagina->destino.to_ulong()];  
    
     // iterar hasta encontrar un vecino directo
    while (destino != -1 && tablaRuta[destino] != -1) {
        destino = tablaRuta[destino];
    }
    // si el destino es un vecino directo, retornar el destino original
    return destino == -1 ? (p->pagina->destino.to_ulong()) : destino;
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
        return 9000;
    }
    return vecinos.buscar(n)->colaDeEspera->size(); 
}

void Router :: impre(){
    vecinos.IRD();
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