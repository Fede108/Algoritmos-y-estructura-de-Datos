#include "../inc/Grafo.h"
#include <iomanip>

using namespace std;

Grafo::Grafo(int N, int K, int a) : matriz(nullptr), N(N) {
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
   //    nodos.resize(N);
    for (int i = 0; i < N; i++) {
        nodos.push( new Router(i, N, K, a)); 
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
    if(K%2){
        for (int i = 0; i < N; i++) {
            int siguiente = (i + K) % N; 
            agregarArco(i, siguiente);
        }
    }
}

void Grafo::agregarArco(int n, int m) {
    if (n >= 0 && n < N && m >= 0 && m < N && n != m) { 
        matriz[n][m] = 1;
        nodos.get(n)->agregarNodoAdyacente(nodos.get(m));
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
            nodos.get(i)->impre();
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
           pesos[i][y] = nodos.get(i)->tamañoCola(y);
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
        nodos.get(i)->actualizarTabla(cf[i]);
    }  
}
