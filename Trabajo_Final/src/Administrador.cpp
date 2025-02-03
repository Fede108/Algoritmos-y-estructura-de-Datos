#include <fstream>
#include <iostream>
#include <iomanip>
#include "../inc/Administrador.h"

using namespace std;

void Administrador::generarDOT(){ 
    ofstream archivo("grafo.dot");
    if(archivo.is_open()){
        archivo << "digraph G {\n" << "    edge [color=gray, penwidth=1];\n" << "    size=\"8,8\";\n" << "    ratio=\"fill\";\n";
        archivo << " subgraph routers {\n";
        archivo << " node [shape=box, style=filled, color=royalblue, fixedsize=true, width=0.5, height=0.5, fontcolor=white];\n";
            for (int i = 0; i < grafo->N; ++i) {
                    archivo << "        " << i << " [label=\"R" << i << "\"];\n";
            }
        archivo << "  }\n";
        archivo << " subgraph terminales {\n";
        archivo << "  node [shape=box, style=filled, color=forestgreen, fixedsize=true, width=0.5, height=0.5, fontcolor=white];\n";
        for (int i = 0; i < grafo->N; ++i) {
            for (int k = 0; k < grafo->t; ++k) {
                if(grafo->nodos.get(i)->terminales.get(k)->pagina)
                    archivo << i << k << " [label=\"T" << k << " [" << grafo->nodos.get(i)->terminales.get(k)->pagina->id << "]\"];\n";
                else
                    archivo << i << k << " [label=\"T" << k << "\"];\n";
            }
        }
        archivo << " }\n";

        for (int i = 0; i < grafo->N; ++i) {
            for (int j = 0; j < grafo->N; ++j) {
                if(grafo->pesos[i][j] != 9000)
                    archivo << "    " << i << " -> " << j << " [label=\"" << grafo->pesos[i][j] << "\"];\n";
            }
        }
        for (int i = 0; i < grafo->nodos.size(); ++i) {
            for (int k = 0; k < grafo->nodos.get(i)->t; ++k) {
                archivo << "    " << i << " -> "  << i << k << " [minlen=0.2];\n";
            }
        }
        archivo << "}\n";
        archivo.close();
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
    grafo->nodos.get(3)->terminales.get(0)->emitirPagina(1,6);
    grafo->nodos.get(3)->terminales.get(0)->emitirPagina(0,5);
//    crearNuevaPagina();
//    crearNuevaPagina();
//    crearNuevaPagina();
    int ciclos = 0;
    generarDOT();
    while (sigue)
    {   
        cout << "\n =========================================== CICLO SIMULACION "<< ciclos<< " ============================================ \n";
        grafo->mostrarCaminos();

        
        cout << "\n--------------------\n\n -- PAQUETES RECIBIDOS-- \n\n";
        for (int i = 0; i < grafo->N; i++)
        {
         grafo->nodos.get(i)->reenvio();  // se realizan las tareas de recepcion, reenvio o almacenamiento        
        }
      //  grafo->matrizPesos();
      //  grafo->mostrarCaminos();
        cout << " --------------------\n \n-- PAQUETES ENVIADOS-- \n";
        for (int i = 0; i < grafo->N; i++)
        {
          grafo->nodos.get(i)->procesamiento();  // se procesan los paquetes y se envian a la cola correspondiente
        } 
        grafo->matrizPesos();
        generarDOT();
        if (ciclos%2) grafo->Floyd();
        char opcion;
        cin >> opcion;
        sigue = (opcion == 's' || opcion == 'S'); // continuar si se ingresa s

        if (++ciclos == 50) sigue = false;
    }
}

void Administrador::crearNuevaPagina(){     
     if (rand() % 100 < 110) { // 40% de probabilidad
            int origenR     =  rand() % grafo->N; 
            int origenT     =  rand() % grafo->t;     
            bitset<8> h_ip  =  rand() % grafo->t;       
            bitset<8> l_ip  =  rand() % grafo->N;      
            int tamaño      = (rand() % 10) + 1;        
            bitset<16> destino((h_ip.to_ulong() << 8) | l_ip.to_ulong());
            grafo->nodos.get(origenR)->terminales.get(origenT)->emitirPagina(destino, tamaño);      
    }
}

int main() {
    Administrador* ad = new Administrador();
    ad->crearRed("cfg.txt");
    ad->simular();
    return 0;
}
