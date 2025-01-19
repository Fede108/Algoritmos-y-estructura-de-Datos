#include <fstream>
#include <iostream>
#include <iomanip>
#include "../inc/Administrador.h"

using namespace std;

void Administrador::generarDOT(){
    ofstream archivo("grafo.dot");
    archivo << "digraph G {\n";
    archivo << "    node [shape=circle, style=filled, color=lightblue];\n";
    archivo << "    edge [color=gray, penwidth=1];\n";
    archivo << "    size=\"8,8\";\n";   // Especificar el tamaño en forma de cadena
    archivo << "    ratio=\"fill\";\n"; // Usar comillas dobles para el valor "fill"
    for (int i = 0; i < grafo->nodos.size(); ++i) {
        for (int j = 0; j < grafo->nodos.get(i)->N; ++j) {
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
    grafo = new Grafo(n, k, 2);
}

void Administrador::simular(){
    grafo->matrizPesos();
    grafo->Floyd();
    grafo->mostrarGrafo();
    srand(time(0));
    int n = rand() % 3;
    int l = rand() % 10;
    int x = rand() % 3;   // destino 
    grafo->nodos.get(2)->terminal->enviarPagina(0);  // origen

    while (1)
    {
       for (int i = 0; i < grafo->N; i++)
       {
            grafo->nodos.get(i)->reenvio();
            grafo->nodos.get(i)->recepcion();
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
   
    Administrador* ad = new Administrador();
    ad->crearGrafo(N,K);
    ad->simular();

    return 0;
}