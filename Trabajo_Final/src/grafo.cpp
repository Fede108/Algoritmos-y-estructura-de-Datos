#include <iostream>
#include <vector>
using namespace std;

class Grafo {
private:
    int **matriz; // Matriz de adyacencia
    int N;        // Número de nodos

public:
    Grafo();
    ~Grafo();
    void crearGrafo(int N, int K);
    void agregarArco(int n, int m);
    void mostrarGrafo();
};

Grafo::Grafo() : matriz(nullptr), N(0) {}

Grafo::~Grafo() {
    if (matriz != nullptr) {
        for (int i = 0; i < N; i++) {
            delete[] matriz[i];
        }
        delete[] matriz;
    }
}

void Grafo::crearGrafo(int N, int K) {
    if (K >= N) {
        cout << "K debe ser menor que N para garantizar conexiones válidas." << endl;
        return;
    }

    this->N = N;

    // Crear la matriz de adyacencia
    matriz = new int *[N];
    for (int i = 0; i < N; i++) {
        matriz[i] = new int[N]();
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

void Grafo::agregarArco(int n, int m) {
    if (n >= 0 && n < N && m >= 0 && m < N && n != m) { // Evitar bucles
        matriz[n][m] = 1;
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
}

