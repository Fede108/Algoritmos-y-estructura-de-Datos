#include <fstream>
#include <iostream>
#include <iomanip>
#include "../inc/Administrador.h"

using namespace std;

void Administrador::generarDOT(){
    ofstream archivo("grafo.dot");
    if (archivo.is_open() ){
    archivo << "digraph G {\n";
    archivo << "    node [shape=circle, style=filled, color=lightblue];\n";
    archivo << "    edge [color=gray, penwidth=1];\n";
    archivo << "    size=\"8,8\";\n";   // Especificar el tamaño en forma de cadena
    archivo << "    ratio=\"fill\";\n"; // Usar comillas dobles para el valor "fill"
    for (int i = 0; i < grafo->nodos.size(); ++i) {
        for (int j = 0; j < grafo->nodos.size(); ++j) {
            if (grafo->pesos[i][j] != 9000) {
                archivo << "    " << i << " -> " << j << " [label=\"" << grafo->pesos[i][j] << "\"];\n";
            }
        }
     for (int k = 0; k < grafo->nodos.get(i)->t; k++)
      {  
        archivo << "    " << i << " -> " << k << i << ";\n";
        if(grafo->nodos.get(i)->terminales.get(k)->pagina)  archivo << "    " << k << i  << " [label=\"" << k << " " <<grafo->nodos.get(i)->terminales.get(k)->pagina->tamaño <<"\"];\n";
        else  archivo << "    " << k << i  << " [label=\"" << k << "\"];\n";
      }
        
    }

    archivo << "}\n";
    //archivo.close();
    }
    cout << "Archivo grafo.dot generado.\n";
}

void Administrador::crearGrafo(int N, int K, int a, int t){
    grafo = new Grafo( N, K, a, t);
}

void Administrador::simular(){
    bool sigue = true;
    srand(time(0));
//    grafo->nodos.get(origen)->terminal->emitirPagina(destino,tamaño);  // origen, destino y tamaño
//    grafo->nodos.get(origen)->terminal->emitirPagina(3,tamaño);  // origen
//    grafo->nodos.get(2)->terminal->emitirPagina(0,10);  // origen
//    grafo->nodos.get(4)->terminal->emitirPagina(1,3);
//    grafo->nodos.get(3)->terminal->emitirPagina(0,3);
//    grafo->nodos.get(5)->terminal->emitirPagina(2,7);
//    grafo->nodos.get(0)->terminal->emitirPagina(5,6);
//    grafo->nodos.get(7)->terminal->emitirPagina(2,8);
//    grafo->nodos.get(1)->terminal->emitirPagina(6,4);
        grafo->nodos.get(2)->terminal->emitirPagina(1,5);
        grafo->nodos.get(3)->terminal->emitirPagina(1,3);
    grafo->matrizPesos();
    grafo->Floyd();
    int ciclos = 0;
    grafo->mostrarGrafo();
    generarDOT();
    while (sigue)
    {  
        
        for (int i = 0; i < grafo->N; i++)
        {
         grafo->nodos.get(i)->reenvio();  // se realizan las tareas de reenvio, recepcion y almacenamiento        
        }
        for (int i = 0; i < grafo->N; i++)
        {
          grafo->nodos.get(i)->procesamiento();  // se procesan los paquetes recibidos asi estan listos para el ciclo siguiente
        }
        grafo->matrizPesos();
        grafo->mostrarCaminos();
        generarDOT();

        if (ciclos%2) grafo->Floyd();
        if (++ciclos == 50) sigue = false;
    }
}

void Administrador::crearNuevaPagina(){
     if (rand() % 100 < 80) { // 80% de probabilidad
            int origen     =  rand() % grafo->N;       // Nodo origen aleatorio
            bitset<8> h_ip = rand() %  grafo->t;  // Parte alta de la IP destino
            bitset<8> l_ip = rand() %  grafo->N;;       // Parte baja de la IP destino
            int tamaño     = (rand() % 10) + 1; // Tamaño aleatorio (1 a 10)
            bitset<16> destino((h_ip.to_ulong() << 8) | l_ip.to_ulong());
            grafo->nodos.get(origen)->terminal->emitirPagina(destino, tamaño);
    }
}

int main() {
    int N = 5; // numero de nodos
    int K = 2; // conexiones por nodo
    int A = 2; // ancho de banda 
    int t = 2; // numero de terminales por nodo
    Administrador* ad = new Administrador();
    ad->crearGrafo(N,K,A,t);
    ad->simular();

    return 0;
} 