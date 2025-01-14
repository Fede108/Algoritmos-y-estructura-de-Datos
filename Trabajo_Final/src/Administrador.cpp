#include <iostream>
#include <vector>
#include <Cola.h>

using namespace std;
class Router
{
private:
    Router* vecino;
    Lista<Router*> *adyacentes;
    int n = 0;
public:
    Router(int n) : n(n){ 
        adyacentes = new Lista<Router*>(); 
    };
    void agregarNodoAdyacente(Router* nodo);
    void impre(){
          if(!adyacentes) adyacentes->impre();
    }
};

void Router::agregarNodoAdyacente(Router* nodo){
    adyacentes->add(nodo);
}

class Grafo
{
private:
    int N; 
    int **matriz;
    vector<Router*> nodos;
    Router* nodo;
public:
    Grafo(int N, int K);
    ~Grafo();
    void agregarArco(int n, int m);
    void mostrarGrafo();    
};

Grafo::Grafo(int N, int K) : matriz(nullptr), N(N) {
    if (K >= N) {
        cout << "K debe ser menor que N para garantizar conexiones válidas." << endl;
        return;
    }

    // Crear la matriz de adyacencia
    matriz = new int *[N];
    for (int i = 0; i < N; i++) {
        matriz[i] = new int[N]();
    }
    // Crea lista de adyacencia 
    nodos.resize(N);
    for (int i = 0; i < N; i++) {
        nodos[i] = new Router(i);
    }
    // Crear el grafo con conexiones uniformes
    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= K / 2; j++) {
            int siguiente = (i + j) % N;          // Conexión hacia adelante
            int anterior = (i - j + N) % N;      // Conexión hacia atrás

            agregarArco(i, siguiente);
            agregarArco(i, anterior);
        }
    }
}

Grafo::~Grafo() {
    if (matriz != nullptr) {
        for (int i = 0; i < N; i++) {
            delete[] matriz[i];
        }
        delete[] matriz;
    }
}


void Grafo::agregarArco(int n, int m) {
    if (n >= 0 && n < N && m >= 0 && m < N && n != m) { // Evitar bucles
        matriz[n][m] = 1;
        nodos[n]->agregarNodoAdyacente(nodos[m]);
    }
}

void Grafo::mostrarGrafo() {
    if (matriz == nullptr) {
        cout << "El grafo no se ha creado." << endl;
        return;
    }

    cout << "Matriz de adyacencia del grafo:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Lista de adyacencia del grafo:" << endl;
    for (int i = 0; i < N; i++) {
        cout << i + 1 << "->";
        for (int j = 0; j < N; j++) {
          nodos.at(j)->impre();
        }
        cout << endl;
    }

}

class Administrador
{
private:
    /* data */
public:
    Administrador(/* args */);
    ~Administrador();
    void crearGrafo(int n, int k);
};


// Ejemplo de uso
int main() {
    int N = 6; // Número de nodos
    int K = 4; // Conexiones por nodo
    Grafo* grafo = new Grafo(N, K);
    grafo->mostrarGrafo();

    return 0;
}