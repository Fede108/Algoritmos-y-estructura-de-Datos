
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
  ExpresionJson* json = new ExpresionJson();
  cout<<json->leer_archivo("data_json.txt")<<endl;
  //json->imprimir_archivo();
  system("PAUSE");
  return EXIT_SUCCESS;
}




