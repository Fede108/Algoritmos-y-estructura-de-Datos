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
        for (int j = 0; j < grafo->nodos.get(i)->N; ++j) {
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
    grafo->matrizPesos();
    grafo->Floyd();
    grafo->mostrarGrafo();
    srand(time(0));
    int n = rand() % 3;
    int l = rand() % 10;
    int x = rand() % 3;   // destino 
 //   grafo->nodos.get(2)->terminal->enviarPagina(0,10);  // origen
    grafo->nodos.get(3)->terminal->enviarPagina(1,5);  // origen
    grafo->nodos.get(3)->terminal->enviarPagina(0,5);  // origen
    int ciclos = 0;
    grafo->mostrarGrafo();
    generarDOT();
    while (sigue)
    {  
        for (int i = 0; i < grafo->N; i++)
       {
            grafo->nodos.get(i)->reenvio();
       }
        for (int i = 0; i < grafo->N; i++)
       {
            grafo->nodos.get(i)->recepcion();
       }
       grafo->matrizPesos();
       grafo->mostrarGrafo();
       generarDOT();
       if(ciclos==1){
            ciclos = 0;
            grafo->Floyd();
       } else{  ciclos++;}
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

/*// Solicitar entrada al usuario
        char opcion;
        cout << "¿Desea continuar con la simulación? (s/n): ";
        cin >> opcion;
        sigue = (opcion == 's' || opcion == 'S'); // Continuar si se ingresa 's' o 'S'*/