#include "../inc/Terminal.h"
#include "../inc/Router.h"

void Terminal :: emitirPagina(bitset<16> destino, int tamaño){   // emite una nueva pagina con un identificador unico
    Pagina* p      = new Pagina(tamaño);
    p->destino     = destino;
    p->origen      = (this->ip.to_ulong() << 8) | this->router->ip.to_ulong();
    p->id          = (nroPagina << 16) | p->origen.to_ulong();
    router->recibirPagina(p);
    nroPagina++;
}

void Terminal :: recibirPagina(Paquete* arreglo){   // recibe la pagina en paquetes
    if (pagina != NULL) delete pagina;
    pagina = arreglo->pagina;
    for (int i = 0; i < pagina->tamaño; i++){
        cout<<arreglo[i].nroPaquete<<endl;
    }
}

void Terminal :: recibirPagina(Pagina* p){    // recibe la pagina completa
    pagina = p;
}
