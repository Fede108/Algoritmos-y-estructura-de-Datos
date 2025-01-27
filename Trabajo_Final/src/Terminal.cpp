#include "../inc/Terminal.h"
#include "../inc/Router.h"

Terminal::Terminal(Router* router,  bitset<8> n )
{
    this->router = router;
    this->ip = n;
}

void Terminal :: enviarPagina(int destino, int tamaño){
    Pagina* p = new Pagina(tamaño);
    p->destino     = destino;
    p->id          = nroPagina;
    p->origen      = this->ip;
    
    router->recibirPagina(p);
    nroPagina++;
}

void Terminal :: recibirPagina(Paquete* arreglo){
    pagina = arreglo->pagina;
    pagina->arr = arreglo;
    for (int i = 0; i < pagina->tamaño; i++)
    {
        cout<<pagina->arr[i].nroPaquete<<endl;
    }
}

void Terminal :: recibirPagina(Pagina* p){
    pagina = p;
}
