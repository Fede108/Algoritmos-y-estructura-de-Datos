#include "../inc/Terminal.h"
#include "../inc/Router.h"

Terminal::Terminal(Router* router)
{
    this->router = router;
   
}

Terminal::~Terminal()
{
}

void Terminal :: enviarPagina(int x){
    Pagina* p = new Pagina();
    p->informacion = 1;
    p->ip = x;
    p->tamaño = 5;
    router->recibirPagina(*p);
}

void Terminal :: recibirPagina(Paquete* p){
   paquetes.add(p);
   return;
}
