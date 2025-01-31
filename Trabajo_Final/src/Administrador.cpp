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
}


void Administrador::crearRed(string cfg){
    bool conexiones = false, routers = false,  terminales = false;
    int i = -1; int y = 0; int N = 0; int T = 0; int** matriz;
    string linea;
    ifstream archivo(cfg);

    if (archivo.is_open() ){
        while(getline(archivo, linea)){
            if(linea == "conexiones") {conexiones = true;}
            else if(conexiones){
                i++; y=0; matriz[i] = new int[N]();
                for (char c : linea) {
                    if (c != ' ' && c != '\t'  && c != ','){
                        matriz[i][y] += c - '0'; 
                    }
                    if (c == ',' ){y++; }
                }   
            }
            else{
                for (char c : linea) {
                    if(c == 'N') { routers = true; }
                    else if(routers)  { N = c - '0'; routers = false; }
                    else if(c == 'T') { terminales = true;}
                    else if(terminales) { T = c - '0'; terminales = false; }
                }
                    matriz = new int *[N];
                }
        }
    }
    grafo = new Grafo(N, T, matriz);
    grafo->mostrarGrafo();
}

void Administrador::simular(){
    bool sigue = true;
    srand(time(0));
    grafo->matrizPesos();
    grafo->Floyd();
    grafo->nodos.get(0)->terminales.get(0)->emitirPagina(1,4);
    grafo->nodos.get(2)->terminales.get(0)->emitirPagina(0,10);
    int ciclos = 0;
    generarDOT();
    while (sigue)
    {   
        cout << "\n ---------------------------------CICLO SIMULACION "<< ciclos<<" ----------------------------------------------- \n";
        grafo->mostrarCaminos();

        crearNuevaPagina();
        cout << "\n -- PAQUETES RECIBIDOS-- \n";
        for (int i = 0; i < grafo->N; i++)
        {
         grafo->nodos.get(i)->reenvio();  // se realizan las tareas de reenvio, recepcion y almacenamiento        
        }
        cout << "\n -----------------\n \n-- PAQUETES ENVIADOS-- \n";
        for (int i = 0; i < grafo->N; i++)
        {
          grafo->nodos.get(i)->procesamiento();  // se procesan los paquetes recibidos asi estan listos para el ciclo siguiente
        } 
        grafo->matrizPesos();
        generarDOT();
        if (ciclos%2) grafo->Floyd();
        if (++ciclos == 50) sigue = false;
    }
}

void Administrador::crearNuevaPagina(){
     
    //        grafo->nodos.get(3)->terminales.get(0)->emitirPagina(1,6);
    //        grafo->nodos.get(3)->terminales.get(0)->emitirPagina(0,5);
    /* if (rand() % 100 < 40) { // 40% de probabilidad
            int origenR     =  rand() % grafo->N;       // Nodo origen aleatorio
            int origenT     =  rand() % grafo->t;       // Terminal origen aleatorio
            bitset<8> h_ip  =  rand() % grafo->t;      // Parte alta de la IP destino
            bitset<8> l_ip  =  rand() % grafo->N;;     // Parte baja de la IP destino
            int tamaño      = (rand() % 10) + 1;         // Tamaño aleatorio (1 a 10)
            bitset<16> destino((h_ip.to_ulong() << 8) | l_ip.to_ulong());
            grafo->nodos.get(origenR)->terminales.get(origenT)->emitirPagina(destino, tamaño);      
    }*/
}

int main() {
    Administrador* ad = new Administrador();
    ad->crearRed("cfg.txt");
    ad->simular();
    return 0;
}



//    grafo->nodos.get(origen)->terminal->emitirPagina(destino,tamaño);  // origen, destino y tamaño
//    grafo->nodos.get(origen)->terminal->emitirPagina(3,tamaño);  // origen
//    grafo->nodos.get(2)->terminal->emitirPagina(0,10);  // origen
//    grafo->nodos.get(4)->terminal->emitirPagina(1,3);
//    grafo->nodos.get(3)->terminal->emitirPagina(0,3);
//    grafo->nodos.get(5)->terminal->emitirPagina(2,7);
//    grafo->nodos.get(0)->terminal->emitirPagina(5,6);
//    grafo->nodos.get(7)->terminal->emitirPagina(2,8);