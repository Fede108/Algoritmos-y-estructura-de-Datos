#include <iostream>
#include <vector>

using namespace std;
int main()
{
    vector <int > g1;
    for (int i = 1; i <= 5; i++)
    g1.push_back(i);
    cout << "Vector: ";
    for (vector <int >:: iterator i = g1.begin (); i != g1.end(); ++i)
        cout << *i << " ";
        cout << endl ;
        cout << "Tamanio"<< g1.size()<< endl;
        cout << "Capacidad"<< g1.capacity()<< endl;
        cout << "Tam. Max."<< g1.max_size()<< endl;
        g1.resize (4);
        cout << "Tamanio: " << g1.size() << endl;
        cout << "Vector: ";
    for (vector <int >:: iterator i = g1.begin (); i != g1.end(); ++i)
        cout << *i << " ";
        cout << endl;
    if (g1.empty() == false)
    cout << "Vector no vacio" << endl;
    else
    cout << "Vector vacio" << endl;
    cout << "g1[2]=" << g1[2] << endl;
    cout << "g1.at(3)=" << g1.at(3) << endl;
    cout << "g1.front ()=" << g1.front() << endl;
    cout << "g1.back ()=" << g1.back() << endl;

 return 0;

}
