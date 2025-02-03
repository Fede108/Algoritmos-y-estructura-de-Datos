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
    leer_archivo("data.txt", T);
    N = T.last()->n + 1;
    T_copy = T.Copy();
    T.VerArbol();
    salida(); cout <<"IRD original"<<endl;
    T.IRD(); cout<<endl;

    cout <<"Arbol pos semicompleto"<<endl;
    mapear(P, &T);
    P.verArbol();
 
    ordenaSeleccion(P,N,cm1,cc1);
    salida(); cout <<"Hojas ordenadas seleccion"<<endl;
    P.ImprimirHojas();
    salida(); cout <<"Hojas ordenadas quick"<<endl;
    ordenaQuickSort(P,1,N,cm2,cc2);
    P.ImprimirHojas();

    salida(); cout <<"IRD copia"<<endl;
    T_copy->IRD();

    cout << "\n " <<" algoritmo seleccion: nro movimientos = "<<cm1<<" nro de comparaciones = "<<cc1<<endl;
    cout << "\n" <<"  algoritmo quickSort: nro movimientos = "<<cm2<<" nro de comparaciones = "<<cc2<<endl;
    

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
            
            i=primero; j=ultimo;    
            while (i < j) { // El bucle se detendrá cuando i >= j
                while (P.posicion(i)->palabra < pivot->palabra){
                    cc++;
                    i++;
                    if(i>ultimo) break;
                } 
                while (P.posicion(j)->palabra >= pivot->palabra){
                    cc++;
                    j--;
                    if(j<primero) break;
                }
                if (i < j) { // Solo intercambiar si i < j
                    P.swap(i,j);
                    cm += 3;
                }
            }
            // pivot se mueve a v[i]
            //  v[i] se mueve a pivot
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

        for(j=i+1;j<=N;j++){  // recorre el subconjunto [i+1:N] n-1 veces
            cc++; // n-i-1 comparaciones 
            if( P.posicion(j)->repeticiones > P.posicion(pos)->repeticiones ){ // si encuentra un elemento con mas repeticiones

                pos = j; // actualiza posicion del max del subconjunto

            }
        }

        P.swap(pos,i);  // intercambia la primer posicion del subconjunto [i:N] con el max 
        cm = cm + 3; // 3(n-1) movimientos
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
            if (c != '\n' && c != ' ' && c != '\t'){
              palabra += c;  
            } else if (!palabra.empty())
            {    
                T.CreaArbolAVL(convertirMayuscula(palabra));
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
                palabraMayus += palabra[i] - 32; // Convertir a mayúscula
            }else{
                palabraMayus += palabra[i]; // Mantener otros caracteres
            }
    }
    return palabraMayus;
}
