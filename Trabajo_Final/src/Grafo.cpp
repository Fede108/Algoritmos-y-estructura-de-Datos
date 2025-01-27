#include "../inc/Grafo.h"
#include <iomanip>

using namespace std;

Grafo::Grafo(int N, int K, int a, int t) : matriz(nullptr), N(N), a(a), K(K) {
    if (K >= N) { cout << "K debe ser menor que N " << endl;
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
    for (int i = 0; i < N; i++) {
        nodos.push( new Router(i, N, a, t)); 
    }
    
    // crea el grafo 
    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= K / 2; j++) {
            int siguiente = (i + j) % N;          // conexion hacia adelante
            int anterior = (i - j + N) % N;       // conexion hacia atras

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
    // verificar la regularidad con la matriz de adyacencia
    bool regular = verificarRegular();
    // verificar que sea fuertemente conectado con dfs algorithm 
}

void Grafo::agregarArco(int n, int m) {
    if (n >= 0 && n < N && m >= 0 && m < N) { 
        if(matriz[n][m] != 0){ // verifica no producir conexiones repetidas
            agregarArco(n,(m+1)%N);
        }
        else if(n == m)  agregarArco(n,(m+1)%N);
        else {
            matriz[n][m] = 1;
            nodos.get(n)->agregarNodoAdyacente(nodos.get(m));
        }
    }
}

bool Grafo::verificarRegular(){
    int k = 0;
    for (int i = 0; i < N; i++)
    {
        for (int y = 0; y < N; y++)
        {
            k += matriz[i][y];
        }
        if(k!=K) return false;
    }
    return true;
}

void Grafo::mostrarGrafo() {
    
       cout << "--- MATRIZ DE ADYACENCIA ---\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << setw(3) << matriz[i][j] << " ";
            }
            cout << endl;
        } 
        
        cout << "\n--- LISTA DE ADYACENCIA ---\n";
        for (int i = 0; i < N; i++) {
            cout << "Nodo " << i << ":[";
            nodos.get(i)->impre();
            cout << "]"<<endl;
        } 

        cout << "\n--- MATRIZ DE PESOS ---\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (pesos[i][j] == 9000) // 9000 representa infinito
                    cout << setw(5) << "INF" << " ";
                else
                    cout << setw(5) << pesos[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\n--- MATRIZ DE CAMINOS ÓPTIMOS ---\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (cf[i][j] == -1)
                    cout << setw(3) << "-1" << " "; 
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
           if(nodos.get(i)->tamañoCola(y) == 9000)  pesos[i][y] = 9000;
           else pesos[i][y] = (nodos.get(i)->tamañoCola(y) / a) + 1; // se pierde un ciclo al entrar y salir del router
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
