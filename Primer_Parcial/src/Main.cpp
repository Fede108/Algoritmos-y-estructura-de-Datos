
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

#include "../inc/State.h"
#include "../inc/Context.h"
#include <vector>


int main()
{ 
  Context* json = new Context();
  cout<<json->leer_archivo("data_json.txt")<<endl;
  //json->imprimir_archivo();
  system("PAUSE");
  return EXIT_SUCCESS;
}




