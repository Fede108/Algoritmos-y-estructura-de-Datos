#include <string>
#include <fstream>
#include "../inc/ArbolPosicional.h"

void ordenaSeleccion(ArbolPosicional &P,int N,int &cm, int &cc);
void mapear(ArbolPosicional &P, ArbolAVL *T);
void leer_archivo(string archivo_,  ArbolAVL &T);
void ordenaQuickSort(ArbolPosicional &P, int primero, int ultimo,int &cm, int &cc);
string convertirMayuscula(string palabra);
void salida();

int main(){
    int cm1 = 0, cc1=0, cm2 = 0, cc2=0, N = 0;
    ArbolAVL T; 
    ArbolAVL *T_copy;
    ArbolPosicional P;

    leer_archivo("data.txt", T);           // lee el archivo y guarda las palabras en el abb en orden alfabetico
    N = T.cabeza()->n + 1;

    salida(); cout <<"ird Abb original"<<"\n"; // impresion en recorrido inorden 
    T.IRD();cout<<endl;                     

    T_copy = T.Copy();                     // se guarda una copia de la lista original
    cout <<"\n-----Abb copia-----"<<"\n\n";
    T.VerArbol();
    
    mapear(P, &T);                         // se mapea la lista en arbol pos, acceso a la lista en orden logaritmico
    cout <<"\n\n-----Arbol pos semicompleto-----\n"<<endl;
    P.verArbol();
 
    ordenaSeleccion(P,N,cm1,cc1);          // ordenamiento de la lista por repeticion
    salida(); 
    cout <<"Hojas ordenadas por repeticion. Algoritmo de seleccion"<<endl;
    P.ImprimirHojas();

    ordenaQuickSort(P,1,N,cm2,cc2);       // ordenamiento de la lista alfabeticamente
    salida(); 
    cout <<"Hojas ordenadas alfabeticamente. Algoritmo quickSort"<<endl;
    P.ImprimirHojas();

    cout << "\n " <<" algoritmo seleccion: nro movimientos = "<<cm1<<" nro de comparaciones = "<<cc1<<endl;
    cout << "\n" <<"  algoritmo quickSort: nro movimientos = "<<cm2<<" nro de comparaciones = "<<cc2<<endl;
    
   
    salida(); cout <<"ird copia"<<endl;
    T_copy->IRD();cout<<endl;  
    salida(); cout <<"ird original"<<"\n"; 
    T.IRD();cout<<endl;                     

    
    cout<<endl;system("PAUSE");
}

void salida(){
    cout << "\n";
    cout << "\n";
    cout << "palabra " << "repeticiones " << "nro nodo----";
   
}

void ordenaQuickSort(ArbolPosicional &P, int primero, int ultimo,int &cm, int &cc){
    int i,j;
    Dato* pivot;
      if(ultimo>primero){
            pivot = P.posicion(ultimo);cm++;
            
            i=primero-1; j=ultimo;    
            while (i < j) { 
                while (P.posicion(++i)->palabra < pivot->palabra){ // continua hasta que el dato sea mayor que el pivot
                    cc++;
                    if(i==ultimo) break; // evita que salga del rango
                } 
                while (P.posicion(--j)->palabra > pivot->palabra){ // continua hasta que el dato sea menor que el pivot
                    cc++;
                    if(j==primero) break; // evita que salga del rango
                }
                if (i < j) { // solo intercambiar si i < j
                    P.swap(i,j);
                    cm += 3;
                }
            }
            //  pivot se mueve a [i]
            //  [i] se mueve a pivot
            P.swap(i,ultimo);
            cm=cm+3;

            ordenaQuickSort(P,primero,i-1,cm,cc);
            ordenaQuickSort(P,i+1,ultimo,cm,cc);
             
      } //fin if 
}// fin ordena


void ordenaSeleccion(ArbolPosicional &P,int N,int &cm, int &cc){
    int i,j,pos;
    
    for(i=1;i<N;i++){ // recorro desde pos 1 a N-1
    
        pos = i; // supone el max como primer posicion subconjunto [i:N-1]

        for(j=i+1;j<=N;j++){  // recorre el subconjunto [i+1:N]   N-1 veces
            cc++; // N-i-1 comparaciones 
            if( P.posicion(j)->repeticiones > P.posicion(pos)->repeticiones ){ // si encuentra un elemento con mas repeticiones

                pos = j; // actualiza posicion del max del subconjunto

            }
        }

        P.swap(pos,i);  // intercambia la primer posicion del subconjunto [i:N] con el max 
        cm = cm + 3; // 3(N-1) movimientos
    }
}


void mapear(ArbolPosicional &P, ArbolAVL *T){  
    P.CreaArbolPos(T);                                                                      
}
    
void leer_archivo(string archivo_,  ArbolAVL &T){
    string palabra;
    ifstream archivo(archivo_);
    if (archivo.is_open() ){
        char c;
        while(archivo.get(c)){
            if (c != '\n' && c != ' ' && c != '\t'){    // mientras no se detecte un delimitador se suman caracteres a la palabra
              palabra += c;  
            } else if (!palabra.empty())   
            {    
                T.CreaArbolAVL(convertirMayuscula(palabra));   // se van agregando las palabras al arbol  
                palabra = ""; 
            }   
        }
        archivo.close();
    }
}

string convertirMayuscula(string palabra){
    string palabraMayus;
    for (int i = 0; i < palabra.length(); i++) {
             if (palabra[i] >= 'a' && palabra[i] <= 'z') {
                palabraMayus += palabra[i] - 32; // convertir a mayuscula     valores ascii: a = 97 ; A = 65
            }else{
                palabraMayus += palabra[i]; // mantener otros caracteres
            }
    }
    return palabraMayus;
}
