

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

#include "../inc/Estado.h"
#include "../inc/ExpresionJson.h"


int main()
{ 
 
  bool sigue = true;
  while(sigue){
    ExpresionJson* json = new ExpresionJson();
    cout<<json->leer_archivo("data.json")<<endl;
    json->generar_archivo();
    char opcion;
    cin >> opcion;
    sigue = (opcion == 's' || opcion == 'S'); // continuar si se ingresa s
  }
     
  return EXIT_SUCCESS;
}




