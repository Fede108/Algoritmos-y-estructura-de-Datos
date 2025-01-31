#include "../inc/Grafo.h"
#include <iomanip>
#define INFI 9000
using namespace std;

Grafo::Grafo(int N, int t, int **matriz) : matriz(matriz), N(N), t(t) {
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
    // crea lista de adyacencia 
    for (int i = 0; i < N; i++) {
        nodos.push(new Router(i, t, cf[i], cf)); 
    }
    // creo el grafo con una matriz, algoritmo de dfs sirve para ver conexiones?
    for (int i = 0; i < N; i++){
        for (int y = 0; y < N; y++){
                if(matriz[i][y]) nodos.get(i)->agregarNodoAdyacente(nodos.get(y), matriz[i][y]);
        }
    }  
}

void Grafo :: matrizPesos(){
    for (int i = 0; i < N; i++)
    {
        for (int y = 0; y < N; y++)
        {
           if(nodos.get(i)->tamañoCola(y) == INFI)  pesos[i][y] = INFI;
           else pesos[i][y] = nodos.get(i)->tamañoCola(y); 
        }
    }
}

void Grafo :: Floyd(){
    int i,j,k;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
                        if(pesos[i][j] == INFI){
                            cf[i][j]=-1;   // -1 si no hay camino directo de i a j 
                            A[i][j] = INFI;
                        } 
                        else{
                            cf[i][j]=j;   // camino de i a j es directo
                            A[i][j]=(pesos[i][j]/ nodos.get(i)->anchoBanda(j)) + 1;  // se pierde un ciclo al entrar y salir del router
                        } 
        }
    }
    for(i=0;i<N;i++) A[i][i]=0;
  
    for(k=0;k<N;k++){     // recorro por cada k nodo intermedio en orden externo
    // recorro la matriz completa para encontrar caminos más cortos
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                            if((A[i][k]+ A[k][j])< A[i][j]){      // si el camino ij es mas corto a traves de k 
                                    A[i][j]= A[i][k]+ A[k][j];    // actualiza el peso minimo
                                    cf[i][j]=k;                   // actualiza nodo intermedio en el camino 
                        }
            }
        }
    }  
}


void Grafo::mostrarGrafo() {
       cout << "\n--- MATRIZ DE ADYACENCIA ---\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << setw(6) << matriz[i][j] << " ";
            }
            cout << endl;
        } 
        
        cout << "\n--- LISTA DE ADYACENCIA ---\n";
        for (int i = 0; i < N; i++) {
            cout << "Nodo " << i << ":[";
            nodos.get(i)->impre();
            cout << "]"<<endl;
        }         
}

void Grafo::mostrarCaminos() {
    cout << "\n------ MATRIZ DE PESOS-------\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (pesos[i][j] == INFI) 
                    cout << setw(5) << "INF" << " ";
                else
                    cout << setw(5) << pesos[i][j] << " ";
            }
            cout << endl;
        }
    cout << "\n---- MATRIZ DE CAMINOS ÓPTIMOS ----\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (cf[i][j] == -1)
                cout << setw(5) << "-1" << " "; 
            else
                cout << setw(5) << cf[i][j] << " ";
        }
        cout << endl;
    }
}

void Grafo::crearGrafo(){
    // crea el grafo con K conexiones por nodo
    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= K / 2; j++) {
            int siguiente = (i + j) % N;          // conexion hacia adelante
            int anterior =  (i - j + N) % N;       // conexion hacia atras
            agregarArco(i, siguiente);
            agregarArco(i, anterior);
        }
    } 
    if(K%2){      // si k es impar
        for (int i = 0; i < N; i++) {
            int siguiente = (i + K) % N; 
            agregarArco(i, siguiente);
        }
    }
}

void Grafo::agregarArco(int n, int m) {
    if (n >= 0 && n < N && m >= 0 && m < N) { 
        if(matriz[n][m] != 0){  // verifica no producir conexiones repetidas
            agregarArco(n,(m+1)%N);
        }
        else if(n == m)  agregarArco(n,(m+1)%N);  // verifica no producir autoconexion
        else {
            matriz[n][m] = 1;
            nodos.get(n)->agregarNodoAdyacente(nodos.get(m),matriz[n][m]);
        }
    }
}