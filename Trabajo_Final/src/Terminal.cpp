#include "../inc/Terminal.h"
#include "../inc/Router.h"

Terminal::Terminal(Router* router,  bitset<4> n )
{
    this->router = router;
    this->n = n;
}

Terminal::~Terminal()
{
}

void Terminal :: enviarPagina(int x){
    Pagina* p = new Pagina();
    p->informacion = 1;
    p->ip = x;
    p->tamaño = 5;
    p->id = 0;
    router->recibirPagina(p);
}

void Terminal :: recibirPagina(Pagina* p){
    pagina = p;
}
