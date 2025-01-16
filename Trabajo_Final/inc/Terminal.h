#ifndef TERMINAL_H
#define TERMINAL_H

class Router;

struct Pagina
{
    int ip = 0;
    int tamaño = 0;
    int informacion = 0;
};

struct Paquete
{
   int ip = 0;
   int nroPaquete = 0;
   int informacion = 0;
};

class Terminal
{
private:
    Router* router;
    Pagina* pagina;
public:
    Terminal(Router* router);
    ~Terminal();
    void enviarPagina();
    void recibirPagina(Paquete* p);
};




#endif 