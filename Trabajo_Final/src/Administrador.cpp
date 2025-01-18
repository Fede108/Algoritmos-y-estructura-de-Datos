
#include <fstream>
#include <iostream>
#include <iomanip>
#include "../inc/Administrador.h"
using namespace std;

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
        nodos[i] = new Router(i, N, K);
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
   // Imprimir matriz de adyacencia
       /* cout << "=== MATRIZ DE ADYACENCIA ===\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << setw(3) << matriz[i][j] << " ";
            }
            cout << endl;
        }
        */
        // Imprimir lista de adyacencia
        cout << "\n=== LISTA DE ADYACENCIA ===\n";
        for (int i = 0; i < N; i++) {
            cout << "Nodo " << i << ":[";
            nodos.at(i)->impre();
            cout << "]"<<endl;
        } 

        // Imprimir matriz de pesos
        cout << "\n=== MATRIZ DE PESOS ===\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (pesos[i][j] == 9000) // 9000 representa infinito
                    cout << setw(5) << "INF" << " ";
                else
                    cout << setw(5) << pesos[i][j] << " ";
            }
            cout << endl;
        }

        // Imprimir matriz de caminos óptimos
        cout << "\n=== MATRIZ DE CAMINOS ÓPTIMOS ===\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (cf[i][j] == -1)
                    cout << setw(3) << "-1" << " "; // Sin nodo intermedio
                else
                    cout << setw(3) << cf[i][j] << " ";
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

void Administrador::generarDOT(){
    ofstream archivo("grafo.dot");
    archivo << "digraph G {\n";
    archivo << "    node [shape=circle, style=filled, color=lightblue];\n";
    archivo << "    edge [color=gray, penwidth=1];\n";
    archivo << "    size=\"5,5\";\n";   // Especificar el tamaño en forma de cadena
    archivo << "    ratio=\"fill\";\n"; // Usar comillas dobles para el valor "fill"
    for (int i = 0; i < grafo->nodos.size(); ++i) {
        for (int j = 0; j < grafo->nodos.at(i)->N; ++j) {
            if (grafo->pesos[i][j] != 9000) {
                archivo << "    " << i << " -> " << j << " [label=\"" << grafo->pesos[i][j] << "\"];\n";
            }
        }
    }
    archivo << "}\n";
    archivo.close();
    cout << "Archivo grafo.dot generado.\n";
}


void Administrador::crearGrafo(int n, int k){
    grafo = new Grafo(n, k);
}

void Administrador::simular(){
    grafo->matrizPesos();
    grafo->Floyd();
    grafo->mostrarGrafo();
    srand(time(0));
    int n = rand() % 4;
    int l = rand() % 10;
    int x = rand() % 4;   // destino 
    grafo->nodos.at(n)->terminal->enviarPagina(x);  // origen

    while (1)
    {
       for (int i = 0; i < grafo->N; i++)
       {
            grafo->nodos.at(i)->enviarPaquete();
            grafo->nodos.at(i)->enviarCola();
       }
       grafo->matrizPesos();
       grafo->Floyd();
       grafo->mostrarGrafo();
       generarDOT();
    
    }
}

int main() {
    int N = 4; // numero de nodos
    int K = 2; // conexiones por nodo
    Grafo* grafo = new Grafo(N, K);
    grafo->matrizPesos();
  //  grafo->mostrarGrafo();
   
    Administrador* ad = new Administrador();
    ad->crearGrafo(N,K);
    ad->simular();

    return 0;
}