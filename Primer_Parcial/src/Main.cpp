
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

#include "../inc/Pila.h"
#include "../inc/Expresion.h"
#include "../inc/Llave_valor.h"
#include "../inc/Cola.h"

#include <vector>

class Json
{
private:
    Pila<char> p ;
    string comando;
    string nombre_archivo;
    vector<string> expresion_json; 
    Llave_valor *llave_valor;
public:
    Json(string nombre_archivo) : nombre_archivo(nombre_archivo) {} ;
    void leer_archivo();
    void lector_linea(int indice, string comando);
    void evaluar_llave(ifstream& archivo);
    void analizador_archivo();
};


void Json ::  leer_archivo(){
    ifstream archivo(nombre_archivo);
    bool linea_nueva = false;
    if (archivo.is_open()) {
        char c;
        archivo.get(c);
        if(c=='{'){
            p.apilar('{');
        }
        if (!p.pilavacia() ){
            evaluar_llave(archivo);
        }
        else{ /* error */ }
           
        
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo." << endl;
        return ; 
    }
}


void Json::evaluar_llave(ifstream& archivo){
    bool correcta = false;
    Pila<char>* pila_llave = new Pila<char>;
    char c;
    while (archivo.get(c) &&  ! correcta )
    {
        comando += c; 
        if (c == '\n' || c == ' ' || c == '\t' ){
        }
        else if (c == '"'  || pila_llave->pilavacia()){ 
            pila_llave->apilar(c);
        }
        else if (c == '"'  || !pila_llave->pilavacia()){ 
            pila_llave->desapilar();
            correcta = true;
        }
    } 
    
    if (correcta)
    {   
        archivo.get(c);
        if (c == '"')
        {
            
        }
        if (c == '[')
        {
            /* code */
        }
    }
    
}


void Json::lector_linea(int indice, string comando){
if(comando.length() == 0) return;
string linea = "";
     for (int i = 0; i < comando.length(); i++)
    {
        if (comando[i] == '\n' || comando[i] == ' ' || comando[i] == '\t' ){}
        else{
            linea += comando[i]; 
        }   
    }
    expresion_json.push_back(linea);
    return;
}

void Json::analizador_archivo(){
    if( expresion_json.front()[0] == '{' ) p.apilar('{');
    if( expresion_json.back()[expresion_json.back().length() - 1] == '}' ){ p.desapilar();}

    
    for (int i = 0; i < expresion_json.size() ;i++)
    {
        llave_valor = new Llave_valor(expresion_json[i]);
        cout<<llave_valor->validar();
        cout<<llave_valor->guardarLinea()<<endl;
    }   
}


int main()
{ 
  Json* json = new Json("data_json.txt");
  json->leer_archivo();
  json->analizador_archivo();
  
}




