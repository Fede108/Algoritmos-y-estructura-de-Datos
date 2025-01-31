#include "../inc/Router.h"
#include "../inc/Tree.h"
#define INFI 9000
using namespace std;

void Router :: almacenar(Paquete* paquete){
    Lista<Paquete*>* bufferPaquetes = bufferPaginas.get(paquete->pagina->id);
    if(!bufferPaquetes)
    { 
        bufferPaquetes = new Lista<Paquete*>;
        bufferPaginas.add(paquete->pagina->id, bufferPaquetes);
    } 
    bufferPaquetes->addOrdenado(paquete);
    
    if(bufferPaquetes->size() == paquete->pagina->tamaño)   // si la pagina ya se encuentra completa
    { 
        Paquete arr[bufferPaquetes->size()]; int i = 0;
        while (!bufferPaquetes->esvacia())
        {
            arr[i++] = *bufferPaquetes->cabeza();
            bufferPaquetes->borrar();
        }
        paquete->pagina->paquetes = arr;
        terminales.get(paquete->pagina->getTermDestino())->recibirPagina(paquete->pagina);
        bufferPaginas.borrar(paquete->pagina->id);
        delete bufferPaquetes;
    }
}

void Router::recibirPagina (Pagina* pagina){
    if( pagina->getRoutDestino() == this->ip) // si la pagina tiene como destino una terminal conectado al router
    {    
        terminales.get(pagina->getTermDestino())->recibirPagina(pagina); 
    } 
    else if( !calcularDestino(pagina->getRoutDestino()) )
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
            procesarPagina->addLast(paquete); // pierdo un ciclo antes de enviar el paquete al vecino
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

        if(impreso){ cout << "\n"; impreso=false;}

        if(!procesarPagina->esvacia())
        {   
            Paquete* p = procesarPagina->cabeza(); procesarPagina = procesarPagina->resto();   // sigo con el resto de los paquetes 
            // buscar el destino e ir agregar a cada cola segun ancho de banda
            destino = calcularDestino(p->pagina->getRoutDestino());  // encuentro el camino optimo
            nodo* vecino = vecinos.buscar(destino);

            if (vecino->paqPagRecibidas++ < vecino->anchoBanda)  // envio paginas segun ancho banda para intercalar con demas maquinas
            {      
                vecino->colaDeEspera->encolar(p);
                this->procesarPagina->borrarDato(p);

                cout << "[Router " << this->ip << "] → [Router " << destino << "] | ";
                imprimirRuta(p); cout << "\n";

                vecinosEncolados.add(vecino->router->ip, vecino);
                idEncolados.encolar(vecino->router->ip);
            }      
        }
        if(!procesarVecinos->esvacia())
        {   
            Paquete* p = procesarVecinos->cabeza();  procesarVecinos = procesarVecinos->resto(); // sigo con el resto de los paquetes 
             // envia a la cola de espera del vecino correspondiente
            destino = calcularDestino(p->pagina->getRoutDestino());    // encuentro el camino optimo
            nodo* vecino  = vecinos.buscar(destino);

            vecino->colaDeEspera->encolar(p);
            this->procesarVecinos->borrarDato(p);

            cout << "[Router " << this->ip << "] → [Router " << destino << "] | ";
            imprimirRuta(p);  cout << "\n";

            vecinosEncolados.add(vecino->router->ip, vecino);
            idEncolados.encolar(vecino->router->ip);
        } 
    }
}

void Router::reenvio(){   // envio paquete al vecino
    Paquete *p;
    Vector<nodo*> listaVecinos = vecinos.listar();

    for (int i = 0; i < listaVecinos.size(); i++)
    {
        int paquetesEnviados = 0; 
        nodo* vecino = listaVecinos.get(i); 
        if(!vecino->colaDeEspera->esvacia() ){cout << "\n";} 

        while (!vecino->colaDeEspera->esvacia() && paquetesEnviados ++ < vecino->anchoBanda)   // mientras la cola de espera tenga paquetes y no se llene ancho banda
        {   p = vecino->colaDeEspera->tope();
            vecino->colaDeEspera->desencolar();

            cout << "[Router " << vecino->router->ip << "] <- [Router " << this->ip << "] | " << "[ID: " << p->pagina->id << "] | Nro Paquete: " << p->nroPaquete
                 << " | Origen: " << p->pagina->getRoutOrigen()<< " | Destino: " << p->pagina->getRoutDestino() << "\n";

            vecino->router->recibirPaquete(p);    
        }
        vecino->paqPagRecibidas = 0; // reinicio para el siguiente ciclo
    }
}  

int Router::calcularDestino(int destino){
    if(tablaRuta[destino] == -1) return 0;
    if(destino == tablaRuta[destino]) return destino;  // si el destino es un vecino directo, retorna el destino 
    destino = tablaRuta[destino]; 
    return calcularDestino(destino);  // recursion hasta encontrar un vecino directo
}


void Router::imprimirRuta(Paquete* p) {
    cout << " [ID: " << p->pagina->id << "] | Nro Paquete: " << p->nroPaquete << " | Ruta: " << this->ip;
    ruta(p->pagina->getRoutDestino(), this->ip);
    cout << " | Origen: " <<  p->pagina->getRoutOrigen() 
         << " | Destino: " << p->pagina->getRoutDestino();
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