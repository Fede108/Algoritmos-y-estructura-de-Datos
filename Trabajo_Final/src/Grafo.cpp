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
    // crea la matriz anterior de cf
    anterior = new int *[N];
    for (int i = 0; i < N; i++) {
        anterior[i] = new int[N]();
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
        nodos.push(new Router(i, t, cf[i], cf, A)); 
    }
    // creo el grafo con una matriz
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
            if(nodos.get(i)->tamañoCola(y) == INFI){
                pesos[i][y] = INFI;
            }
            else{
                 pesos[i][y] = nodos.get(i)->tamañoCola(y);
            }

            if(y!=i){
                if (cf[i][y] == -1) A[i][y] = INFI;  // si no hay camino
                else if (cf[i][y] == y){                     
                    A[i][y] = nodos.get(i)->ciclos(y); // si el camino es directo
                }             
                else{
                    A[i][y] = nodos.get(i)->ciclos(cf[i][y]) + A[cf[i][y]][y];  // si hay un nodo intermedio en el camino
                }
            }  
        }
    }
}

void Grafo::Floyd(){
    int i,j,k;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
                        if(pesos[i][j] == INFI){
                            cf[i][j]=-1;   // -1 si no hay camino directo de i a j 
                            A[i][j] = INFI;
                        } 
                        else{
                            cf[i][j]=j;   // camino de i a j es directo       
                            A[i][j] = nodos.get(i)->ciclos(j);  // se pierde un ciclo al entrar y salir del router
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
                cout << setw(5) << matriz[i][j] << " ";
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
    cout << "\n--- MATRIZ DE ADYACENCIA ---" << setw(N*3)<<" "<< "--- MATRIZ DE PESOS ---\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << setw(N) << matriz[i][j] << " ";
            }
            cout << setw(N*3)<< " "; // Espacio entre matrices
            for (int j = 0; j < N; j++) {
                if (pesos[i][j] == INFI) 
                    cout << setw(N) << "INF" << " ";
                else
                    cout << setw(N) << pesos[i][j] << " ";
                }
            cout << endl;
        } 
    
    cout << "\n--- MATRIZ DE CICLOS ---"<< setw(N*3)<< " " <<"--- MATRIZ DE CAMINOS ---\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(N) << A[i][j] << " "; // Imprime la matriz de ciclos
        }
        cout << setw(N*3)<< " "; // Espacio entre matrices
        for (int j = 0; j < N; j++) {
            if (cf[i][j] == -1)
                cout << setw(N) << "-1" << " ";
            else if (cf[i][j] != anterior[i][j])
                cout << setw(N-1) << "*" << cf[i][j] << "*";
            else
                cout << setw(N) << cf[i][j] << " ";
            anterior[i][j] = cf[i][j]; // Actualiza el valor anterior
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