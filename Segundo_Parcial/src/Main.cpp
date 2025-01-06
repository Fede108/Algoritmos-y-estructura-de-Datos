#include <string>
#include <fstream>

#include "../inc/Lista.h"
#include "../inc/Arbol.h"

using namespace std;

int main(){
    Lista *list = new Lista();
    ArbolAVL T;
    leer_archivo("data", *list,T);
    T.VerArbol();
    cout<<endl;system("PAUSE");
    
}

void leer_archivo(string archivo_, Lista &list, ArbolAVL &T){
    string palabra;
    ifstream archivo(archivo_);
    if (archivo.is_open() ){
        char c;
        while(archivo.get(c)){
            if (isalnum(c)){
              palabra += c;  
            } else if (!palabra.empty())
            {    
                add(palabra, list, T);
                palabra = ""; 
            }   
        }
        archivo.close();
    }
}

void add(string palabra, Lista &list, ArbolAVL &T) {
  list.add(palabra);
  T.CreaArbolAVL(palabra);
}