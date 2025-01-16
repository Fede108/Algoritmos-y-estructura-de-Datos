#include "../inc/Terminal.h"
Terminal::Terminal(Router* router)
{
    this->router = router;
    pagina = new Pagina();
    pagina->informacion = 1;
    pagina->ip = 6;
    pagina->tamaño = 20;
}

Terminal::~Terminal()
{
}

void Terminal :: enviarPagina(){
    router->recibirPagina(*pagina);
}

