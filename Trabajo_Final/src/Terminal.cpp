#include "../inc/Terminal.h"
#include "../inc/Router.h"

void Terminal :: emitirPagina(bitset<16> destino, int tamaño){   // emite una nueva pagina con un identificador unico
    Pagina* p = new Pagina(tamaño);  
    p->destino = destino;  
    p->origen  = (this->ip << 8) | this->router->ip;  
    p->id      = (nroPagina << 16) | p->origen.to_ulong();  

    cout << "\n -- PAGINA EMITIDA DESDE EL ROUTER " << this->router->ip<< "\n" << " [ID: " << p->id << "] | Tamaño: " << p->tamaño  << " | Origen: " << this->router->ip  
         << " → Destino: " << p->getRoutDestino() << "\n"; 
          
    router->recibirPagina(p);  
    nroPagina++;  
    
}

void Terminal :: recibirPagina(Pagina* p){    // recibe la pagina completa
    if (pagina != nullptr) delete pagina;
    pagina = p;
    cout << "\n ¡PAGINA COMPLETA! " << " ID: "<< pagina->id << " Tamaño: "<< pagina->tamaño <<" [" ;
    for (int i = 0; i < pagina->tamaño; i++){
        cout<<" "<< pagina->paquetes[i].nroPaquete<<" ";
    }
    cout<<"] " <<"Destino: "<< pagina->getRoutDestino() <<  " \n\n";
}
