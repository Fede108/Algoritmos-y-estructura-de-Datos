#include "../inc/Terminal.h"
#include "../inc/Router.h"

void Terminal :: emitirPagina(bitset<16> destino, int tamaño){   // emite una nueva pagina con un identificador unico
    Pagina* p      = new Pagina(tamaño);
    p->destino     = destino;
    p->origen      = (this->ip.to_ulong() << 8) | this->router->ip.to_ulong();
    p->id          = (nroPagina << 16) | p->origen.to_ulong();
    cout << "\n ID: "<< p->id <<"\n"<<" Tamaño: "<<p->tamaño<< "\n" <<" Origen: "<< this->router->ip.to_ulong() << " -> "<<"Destino: "<< p->destino.operator&=(0xff).to_ulong()<< "\n";
    router->recibirPagina(p);
    nroPagina++;
    
}

void Terminal :: recibirPagina(Paquete* arreglo){   // recibe la pagina en paquetes
    if (pagina != nullptr) delete pagina;
    pagina = arreglo->pagina;
    cout << "\n ID: "<< arreglo->pagina->id << 
    " Tamaño: "<< arreglo->pagina->tamaño <<" [" ;
    for (int i = 0; i < pagina->tamaño; i++){
        cout<<" "<<arreglo[i].nroPaquete<<" ";
    }
    cout<<"] " <<"Destino: "<< arreglo->pagina->destino.operator&=(0xff).to_ulong() <<  " \n";
}

void Terminal :: recibirPagina(Pagina* p){    // recibe la pagina completa
    if (pagina != nullptr) delete pagina;
    pagina = p;
}
