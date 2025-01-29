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
        Paquete arr[bufferPaquetes->size()];
        int i = 0;
        while (!bufferPaquetes->esvacia())
        {
            arr[i++] = *bufferPaquetes->cabeza();
            bufferPaquetes->borrar();
        }
        terminales.get(paquete->pagina->getByteMSB())->recibirPagina(arr);
        bufferPaginas.borrar(paquete->pagina->id);
        delete bufferPaquetes;
    }
}

void Router::recibirPagina (Pagina* pagina){
    if( pagina->getByteLSB() == ip.to_ulong() ) {   // si la pagina tiene como destino una terminal conectado al router
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
    if( paquete->pagina->getByteLSB() == ip.to_ulong() ) {   // si el paquete tiene como destino una terminal conectado al router
       almacenar(paquete);
    }
    else{
        procesarVecinos->addLast(paquete);  // pierdo un turno antes de enviar el paquete al vecino
    }           
}

void Router :: procesamiento(){
    Vector<nodo*> listaVecinos = vecinos.listar();
    for (int i = 0; i < listaVecinos.size(); i++)
    {   listaVecinos.get(i)->cantEnviados = 0;
    }
    enviarColaEspera(procesarPagina, procesarVecinos);
}

void Router::enviarColaEspera(Lista<Paquete*> *procesarPagina, Lista<Paquete*> *procesarVecinos) // guardo en la cola del vecino correspondiente segun camino optimo
{   
    int destino; int a = 0;

    while( !procesarPagina->esvacia() || !procesarVecinos->esvacia() ){
        if(!procesarPagina->esvacia()){   Paquete* p = procesarPagina->cabeza(); procesarPagina = procesarPagina->resto();   // sigo con el resto de los paquetes 
            // buscar el destino e ir agregar a cada cola segun ancho de banda
            destino = calcularDestino(p->pagina->getByteLSB());    // encuentro el camino optimo
             nodo* vecino = vecinos.buscar(destino);
            if (vecino->cantEnviados < A){    // envio paginas segun ancho banda para intercalar con demas maquinas
                vecino->colaDeEspera->encolar(p);
                this->procesarPagina->borrarDato(p);
                vecino->cantEnviados++; 
            }      
        }
        if(!procesarVecinos->esvacia()){   Paquete* p = procesarVecinos->cabeza();  procesarVecinos = procesarVecinos->resto(); // sigo con el resto de los paquetes 
             // envia a la cola de espera del vecino correspondiente
            destino = calcularDestino(p->pagina->getByteLSB());    // encuentro el camino optimo
             nodo* vecino  = vecinos.buscar(destino);                     
            vecino->colaDeEspera->encolar(p);
            this->procesarVecinos->borrarDato(p); 
        } 
    }
}

void Router::reenvio(){   // envio paquete al vecino
    Paquete *p;
    Vector<nodo*> listaVecinos = vecinos.listar();
    for (int i = 0; i < listaVecinos.size(); i++)
    {
        int a = 0;
        while (!listaVecinos.get(i)->colaDeEspera->esvacia() && a++<A )   // mientras la cola de espera tenga paquetes y no se llene ancho banda
        {
            p = listaVecinos.get(i)->colaDeEspera->tope();
 
        //   cout << "\n ID: "<< p->pagina->id <<"\n Nro: "<<p->nroPaquete<<"\n Ruta: "<< this->ip.to_ulong() << " -> "<<listaVecinos.get(i)->router->ip.to_ulong()<< " \n";
        //    cout<<" Origen: "<< p->pagina->origen.operator&=(0xFF).to_ulong()<< " -> "<<"Destino: "<<p->pagina->getByteLSB()<<"\n";

            listaVecinos.get(i)->colaDeEspera->desencolar();
            listaVecinos.get(i)->router->recibirPaquete(p);    
        }
    }
}  

int Router::calcularDestino(int destino){
    if(tablaRuta[destino] == -1){
        cout<< "No hay camino "; return 0;
    }
    if(destino == tablaRuta[destino]) return destino;  // si el destino es un vecino directo, retorna el destino 
    destino = tablaRuta[destino]; 
    return calcularDestino(destino);  // recursion hasta encontrar un vecino directo
}

void Router :: agregarNodoAdyacente(Router* router){
    vecinos.agregarNodo(router);
}

int Router :: tamañoCola(int n) {
    if (!vecinos.buscar(n)) return INFI;
    return vecinos.buscar(n)->colaDeEspera->size(); 
}

void Router :: impre(){
    vecinos.IRD();
}