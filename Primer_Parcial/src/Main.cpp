
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
  json->leer_archivo("data_json.txt");
  system("PAUSE");
  return EXIT_SUCCESS;

}




