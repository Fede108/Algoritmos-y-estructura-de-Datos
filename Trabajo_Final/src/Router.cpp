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
        paquete->pagina->paquetes = arr;
        terminales.get(paquete->pagina->getByteMSB())->recibirPagina(paquete->pagina);
        bufferPaginas.borrar(paquete->pagina->id);
        delete bufferPaquetes;
    }
}

void Router::recibirPagina (Pagina* pagina){
    if( pagina->getByteLSB() == ip.to_ulong() ) {   // si la pagina tiene como destino una terminal conectado al router
        terminales.get(pagina->getByteMSB())->recibirPagina(pagina); 
    } else if( !calcularDestino(pagina->getByteLSB()) ){
        // no se envia la pagina
         cout<< " ¡NO HAY RUTA! No se puede enviar\n ";
    } 
    else{
        // dividir pagina en paquetes segun su tamaño
        for (int i = 0; i < pagina->tamaño ; i++)   
        {
            Paquete* paquete = new Paquete();
            paquete->nroPaquete = i;
            paquete->pagina = pagina;
            procesarPagina->addLast(paquete); // pierdo un ciclo antes de enviar el paquete al vecino
        }
    }
}
    
void Router::recibirPaquete(Paquete* paquete){ // recibo paquete del vecino
    if( paquete->pagina->getByteLSB() == ip.to_ulong() ) {   // si el paquete tiene como destino una terminal conectado al router
       almacenar(paquete);
    }
    else{
        procesarVecinos->addLast(paquete);  // pierdo un ciclo antes de enviar el paquete al vecino
    }           
}

void Router :: procesamiento(){
    enviarColaEspera(procesarPagina, procesarVecinos);
}

void Router::enviarColaEspera(Lista<Paquete*> *procesarPagina, Lista<Paquete*> *procesarVecinos) // guardo en la cola del vecino correspondiente segun camino optimo
{   
    int destino; bool impreso = true;
    while( !procesarPagina->esvacia() || !procesarVecinos->esvacia() ){

        if(impreso){ cout << "\n -- PAQUETES ENVIADOS DESDE EL ROUTER " << this->ip.to_ulong() << " --"; impreso=false;}

        if(!procesarPagina->esvacia()){   Paquete* p = procesarPagina->cabeza(); procesarPagina = procesarPagina->resto();   // sigo con el resto de los paquetes 
            // buscar el destino e ir agregar a cada cola segun ancho de banda
            destino = calcularDestino(p->pagina->getByteLSB());  // encuentro el camino optimo
            nodo* vecino = vecinos.buscar(destino);
            if (vecino->paqPagRecibidas < vecino->anchoBanda){      // envio paginas segun ancho banda para intercalar con demas maquinas
                vecino->colaDeEspera->encolar(p);
                this->procesarPagina->borrarDato(p);
                vecino->paqPagRecibidas++;
                imprimirRuta(p); 
            }      
        }
        if(!procesarVecinos->esvacia()){   Paquete* p = procesarVecinos->cabeza();  procesarVecinos = procesarVecinos->resto(); // sigo con el resto de los paquetes 
             // envia a la cola de espera del vecino correspondiente
            destino = calcularDestino(p->pagina->getByteLSB());    // encuentro el camino optimo
            nodo* vecino  = vecinos.buscar(destino);
            vecino->colaDeEspera->encolar(p);
            this->procesarVecinos->borrarDato(p);
            imprimirRuta(p);  
        } 
    }
    if(!impreso) cout<<"\n";
}

void Router::reenvio(){   // envio paquete al vecino
    Paquete *p;
    Vector<nodo*> listaVecinos = vecinos.listar();
    for (int i = 0; i < listaVecinos.size(); i++)
    {
        int a = 0;
        if(!listaVecinos.get(i)->colaDeEspera->esvacia() ){
            cout << "\n -- PAQUETES RECIBIDOS EN EL ROUTER " << listaVecinos.get(i)->router->ip.to_ulong() <<" DESDE ROUTER "<<this->ip.to_ulong()<< " --\n";
         } 
        while (!listaVecinos.get(i)->colaDeEspera->esvacia() && a++ < listaVecinos.get(i)->anchoBanda)   // mientras la cola de espera tenga paquetes y no se llene ancho banda
        {   p = listaVecinos.get(i)->colaDeEspera->tope();
            listaVecinos.get(i)->colaDeEspera->desencolar();

            cout << "[ID: " << p->pagina->id << "] | Nro Paquete: " << p->nroPaquete << " | Origen: " << p->pagina->origen.to_ulong()<< " | Destino: " << p->pagina->getByteLSB() << "\n";
            
            listaVecinos.get(i)->router->recibirPaquete(p);

                  
        }
        listaVecinos.get(i)->paqPagRecibidas = 0; // reinicio para el siguiente ciclo
    }
}  

int Router::calcularDestino(int destino){
    if(tablaRuta[destino] == -1){
        return 0;
    }
    if(destino == tablaRuta[destino]) return destino;  // si el destino es un vecino directo, retorna el destino 
    destino = tablaRuta[destino]; 
    return calcularDestino(destino);  // recursion hasta encontrar un vecino directo
}


void Router::imprimirRuta(Paquete* p) {
    cout << "\n[ID: " << p->pagina->id << "] | Nro Paquete: " << p->nroPaquete << " | Ruta: " << this->ip.to_ulong();
    ruta(p->pagina->getByteLSB(), this->ip.to_ulong());
    cout << " | Origen: " << (p->pagina->origen.operator&=(0xFF)).to_ulong() 
         << " | Destino: " << p->pagina->getByteLSB();
}

void Router::ruta(int destino, int origen) {
    if (destino == caminos[origen][destino]) {
        cout << " → " << destino;
        return;
    }
    cout << " → " << caminos[origen][destino];
    ruta(destino, caminos[origen][destino]);
}

void Router :: agregarNodoAdyacente(Router* router, int anchoBanda){
    vecinos.agregarNodo(router, anchoBanda);
}

int Router :: tamañoCola(int n) {
    if (!vecinos.buscar(n)) return INFI;
    return vecinos.buscar(n)->colaDeEspera->size(); 
}

int Router :: anchoBanda(int n) {
    if (!vecinos.buscar(n)) return INFI;
    return vecinos.buscar(n)->anchoBanda; 
}

void Router :: impre(){
    vecinos.IRD();
}