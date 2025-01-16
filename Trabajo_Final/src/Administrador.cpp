#include "../inc/Administrador.h"

Grafo::Grafo(int N, int K) : matriz(nullptr), N(N) {
    if (K >= N) { cout << "K debe ser menor que N para garantizar conexiones válidas." << endl;
        return;
    }
    // crea la matriz cf
    cf = new int *[N];
    for (int i = 0; i < N; i++) {
        cf[i] = new int[N]();
    }
    // crea la matriz A
    A = new int *[N];
    for (int i = 0; i < N; i++) {
        A[i] = new int[N]();
    }
    // crea la matriz de pesos
    pesos = new int *[N];
    for (int i = 0; i < N; i++) {
        pesos[i] = new int[N]();
    }
    // crea la matriz de adyacencia
    matriz = new int *[N];
    for (int i = 0; i < N; i++) {
        matriz[i] = new int[N]();
    }
    // crea lista de adyacencia 
    nodos.resize(N);
    for (int i = 0; i < N; i++) {
        nodos[i] = new Router(i, N);
    }
    
    // crea el grafo con conexiones uniformes
    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= K / 2; j++) {
            int siguiente = (i + j) % N;          // Conexión hacia adelante
            int anterior = (i - j + N) % N;       // Conexión hacia atrás

            agregarArco(i, siguiente);
            agregarArco(i, anterior);
        }
    }
}


void Grafo::agregarArco(int n, int m) {
    if (n >= 0 && n < N && m >= 0 && m < N && n != m) { 
        matriz[n][m] = 1;
        nodos[n]->agregarNodoAdyacente(nodos[m]);
    }
}

void Grafo::mostrarGrafo() {
    cout << "Matriz de adyacencia del grafo:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Lista de adyacencia del grafo:" << endl;
    for (int i = 0; i < N; i++) {
        cout << i << "->";
        nodos.at(i)->impre();
        cout << endl;
    }

    cout << "Matriz de pesos del grafo:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << pesos[i][j] << " ";
        }
        cout << endl;
    }
}

void Grafo :: matrizPesos(){
    for (int i = 0; i < N; i++)
    {
        for (int y = 0; y < N; y++)
        {
           pesos[i][y] = nodos.at(i)->tamañoCola(y);
        }
    }
}

void Grafo :: Floyd(){
    int i,j,k;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
                        A[i][j]=pesos[i][j]; cf[i][j]=-1;
        }
    }
    for(i=0;i<N;i++) A[i][i]=0;
  
    for(k=0;k<N;k++){
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                            if((A[i][k]+ A[k][j])< A[i][j]){
                                    A[i][j]= A[i][k]+ A[k][j];
                                    cf[i][j]=k;
                        }
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        nodos.at(i)->actualizarTabla(cf[i]);
    }
    
}


int main() {
    int N = 10; // numero de nodos
    int K = 4; // conexiones por nodo
    Grafo* grafo = new Grafo(N, K);
    grafo->matrizPesos();
    grafo->mostrarGrafo();
    grafo->Floyd();

    return 0;
}