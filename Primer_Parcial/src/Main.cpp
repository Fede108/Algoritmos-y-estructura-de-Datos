#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

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
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  ExpresionJson* json = new ExpresionJson();
  cout<<json->leer_archivo("data_json.txt")<<endl;
  json->generar_archivo();

   int* prueba = new int[5]; // Fuga intencional
   // Forzar generación del reporte
    _CrtDumpMemoryLeaks();
    
  system("PAUSE");

 

  return EXIT_SUCCESS;
}




