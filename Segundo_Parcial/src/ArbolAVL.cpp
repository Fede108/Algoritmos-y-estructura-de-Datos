#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

struct dato
{
    string palabra;
    int repeticiones;
};

struct nodo {
    dato* info;
    nodo* der, * izq, *siguiente;
    int FB;
};

class ArbolAVL
{
private:
    /* data */
public:
    ArbolAVL(/* args */);
    ~ArbolAVL();
};



