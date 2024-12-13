#include <iostream>
using namespace std;
class Lista{
    private:
        int d;
        Lista *next;

    public:
        Lista();
        void add_last(int x);
        void imprimir();
        bool empty();

};

Lista :: Lista(){
    next = nullptr;

}

bool Lista::empty(){
    return next == nullptr;
}


void Lista::add_last(int x){
    Lista *add = new Lista();
    if (empty()){
        next = add;
        add->d = x;
        add->next = nullptr;
        return;
    }
    Lista *aux = next;
    while ( aux->next != nullptr)
    {
        aux = aux->next;         
    }
    add->d = x;
    add->next = nullptr;
    aux->next = add;
}

void Lista::imprimir(){
    if( !empty()){
        Lista *aux = new Lista();
        aux = next;
        while (aux != nullptr)
        {   
            cout<<endl<<aux->d<<endl;
            aux = aux->next;
        }

    }
}

int main(int argc, char *argv[]){
    Lista l;
    l.add_last(4);
    l.add_last(5);
    l.add_last(6);
    l.add_last(7);
    l.imprimir();
}