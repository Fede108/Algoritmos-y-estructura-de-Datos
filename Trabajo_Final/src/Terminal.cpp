#include "../inc/Terminal.h"
#include "../inc/Router.h"

void Terminal :: emitirPagina(bitset<16> destino, int tamaño){   // emite una nueva pagina con un identificador unico
    Pagina* p = new Pagina(tamaño);  
    p->destino = destino;  
    p->origen = (this->ip.to_ulong() << 8) | this->router->ip.to_ulong();  
    p->id = (nroPagina << 16) | p->origen.to_ulong();  

    cout << "\n -- PAGINA EMITIDA DESDE EL ROUTER " << this->router->ip.to_ulong()<< "\n";
    cout << " [ID: " << p->id << "] | Tamaño: " << p->tamaño  << " | Origen: " << this->router->ip.to_ulong()  
         << " → Destino: " << (p->destino.operator&=(0xff)).to_ulong() << "\n"; 
          
    router->recibirPagina(p);  
    nroPagina++;  
    
}

void Terminal :: recibirPagina(Pagina* p){    // recibe la pagina completa
    if (pagina != nullptr) delete pagina;
    pagina = p;
    cout << "\n ¡PAGINA COMPLETA! ";
    cout << " ID: "<< pagina->id << 
    " Tamaño: "<< pagina->tamaño <<" [" ;
    for (int i = 0; i < pagina->tamaño; i++){
        cout<<" "<< pagina->paquetes[i].nroPaquete<<" ";
    }
    cout<<"] " <<"Destino: "<< pagina->destino.operator&=(0xff).to_ulong() <<  " \n\n";
}
