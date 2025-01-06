#include <string>
#include <fstream>

#include "../inc/ListaConAbb.h"

using namespace std;

void add(string palabra, ArbolAVL &T) {
  T.CreaArbolAVL(palabra);
}

void leer_archivo(string archivo_,  ArbolAVL &T){
    string palabra;
    ifstream archivo(archivo_);
    if (archivo.is_open() ){
        char c;
        while(archivo.get(c)){
            if (isalnum(c)){
              palabra += c;  
            } else if (!palabra.empty())
            {    
                add(palabra, T);
                palabra = ""; 
            }   
        }
        archivo.close();
    }
}

int main(){
    ArbolAVL T;
    ArbolAVL *T_copy;
    leer_archivo("data.txt", T);
    T_copy = T.Copy();
    T.VerArbol();
    T.IRD();
    cout << "\n";
    T.print();
    cout<<endl;system("PAUSE");
}
