#include "../inc/Terminal.h"
#include "../inc/Router.h"

Terminal::Terminal(Router* router)
{
    this->router = router;
    pagina = new Pagina();
    pagina->informacion = 1;
    pagina->ip = 2;
    pagina->tamaño = 20;
}

Terminal::~Terminal()
{
}

void Terminal :: enviarPagina(){
    router->recibirPagina(*pagina);
}

void Terminal :: recibirPagina(Paquete* p){
    return;
}
