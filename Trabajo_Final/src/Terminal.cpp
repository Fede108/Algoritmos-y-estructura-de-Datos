#include "../inc/Terminal.h"
#include "../inc/Router.h"

Terminal::Terminal(Router* router,  bitset<8> n )
{
    this->router = router;
    this->ip = n;
}


void Terminal :: enviarPagina(int destino, int tamaño){
    Pagina* p = new Pagina();
    p->informacion = 1;
    p->destino     = destino;
    p->tamaño      = tamaño;
    p->id          = nroPagina;
    p->origen      = this->ip;
    
    router->recibirPagina(p);
    nroPagina++;
}

void Terminal :: recibirPagina(Pagina* p){
    pagina = p;
}
