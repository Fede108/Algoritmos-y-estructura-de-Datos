#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

class Tiempo {

public:
    Tiempo(int = 0, int = 0, int = 0); // constructor predeterminado
    ~Tiempo(); // destructor predeterminado
    // funciones establecer = set
    void estableceHora(int, int, int); // establece hora, minuto, segundo
    void set_hora(int);
    void estableceHora1(int);   // establece hora
    void estableceMinuto(int);  // establece minuto
    void estableceSegundo(int); // establece segundo

    // funciones obtener = get
    int obtieneHora1();        // obtiene hora
    int obtieneMinuto();       // obtiene minuto
    int obtieneSegundo();      // obtiene segundo

    void imprimeUniversal();         // imprime la hora en formato universal
    void imprimeEstandar();          // imprime la hora en formato est�ndar

    void incrementaSegundos(const int);
    void incrementaMinutos(const int);
    void incrementaHoras(const int);
private:
    int hora;     // 0 - 23 (formato de reloj de 24 horas)
    int minuto;   // 0 - 59
    int segundo;  // 0 - 59

}; // fin de la clase Tiempo

// funci�n constructor para inicializar datos privados;
// llama a la funci�n miembro estableceHora para asignar los valores;
// los valores predeterminados son 0 (vea la definic�n de la clase)
Tiempo::Tiempo(int hr, int min, int seg)
{
    cout << "\n soy el constructor\n";
    estableceHora(hr, min, seg);

} // fin del constructor Tiempo
Tiempo::~Tiempo()
{
    cout << "\n soy el destructor ------------";
}
// establece los valores de hora, minuto y segundo
void Tiempo::estableceHora(int h, int m, int s)
{
    estableceHora1(h);
    estableceMinuto(m);
    estableceSegundo(s);

} // fin de la funci�n estableceHora

void Tiempo::set_hora(int h) {
    hora = h;
}
// establece el valor de hora
void Tiempo::estableceHora1(int h)
{
    hora = (h >= 0 && h < 24) ? h : 0;

} // fin de la funci�n estableceHora1

// establece el valor de minuto
void Tiempo::estableceMinuto(int m)
{
    minuto = (m >= 0 && m < 60) ? m : 0;

} // fin de la funci�n estableceMinuto

// establece el valor de segundo
void Tiempo::estableceSegundo(int s)
{
    segundo = (s >= 0 && s < 60) ? s : 0;

} // fin de la funci�n estableceSegundo

// devuelve el valor de hora
int Tiempo::obtieneHora1()
{
    return hora;

} // fin de la funci�n obtieneHora1

// devuelve el valor de minuto 
int Tiempo::obtieneMinuto()
{
    return minuto;

} // fin de la funci�n obtieneMinuto

// devuelve el valor de segundo 
int Tiempo::obtieneSegundo()
{
    return segundo;

} // fin de la funci�n obtieneSegundo

// imprime Tiempo en formato universal
void Tiempo::imprimeUniversal()
{
    cout << setfill('0') << setw(2) << hora << ":"
        << setw(2) << minuto << ":"
        << setw(2) << segundo;

} // fin de la funci�n imprimeUniversal

// print Time in standard format
// imprime Tiempo en formato est�ndar
void Tiempo::imprimeEstandar()
{
    cout << ((hora == 0 || hora == 12) ? 12 : hora % 12)
        << ":" << setfill('0') << setw(2) << minuto
        << ":" << setw(2) << segundo
        << (hora < 12 ? " AM" : " PM");

} // fin de la funcion imprimeEstandar
void Tiempo::incrementaSegundos(const int cuenta)
{
    cout << "Incrementa segundo " << cuenta
        << " veces:\nHora inicio: ";
    imprimeEstandar();

    for (int i = 0; i < cuenta; i++) {
        estableceSegundo((obtieneSegundo() + 1) % 60);

        if (obtieneSegundo() == 0)
            incrementaMinutos(1);

        cout << "\nsegundo + 1: ";
        imprimeEstandar();

    } // fin de for

    cout << endl;

} // fin de la funci�n incrementaSegundos

void Tiempo::incrementaMinutos(const int cuenta)
{
    cout << "Incrementa minuto " << cuenta
        << " veces:\nHora inicio: ";
    imprimeEstandar();

    for (int i = 0; i < cuenta; i++) {
        estableceMinuto((obtieneMinuto() + 1) % 60);

        if (obtieneMinuto() == 0)
            incrementaHoras(1);

        cout << "\nminuto + 1: ";
        imprimeEstandar();

    } // fin de for

    cout << endl;

} // fin de la funci�n incrementaMinutos

void Tiempo::incrementaHoras(const int cuenta)
{
    cout << "Incrementa hora " << cuenta
        << " veces:\nHora inicio: ";
    imprimeEstandar();

    for (int i = 0; i < cuenta; i++) {
        estableceHora1((obtieneHora1() + 1) % 24);

        cout << "\nhora + 1: ";
        imprimeEstandar();

    } // fin de for

    cout << endl;

} // fin de la funci�n incrementaHoras

/*
Hacer una clase Semana_Laboral
que almacene:
el Nombre de un empleado
su documento
en un arreglo de 5 x 2 de tipo Tiempo la hora de ingreso y de salida de cada d�a
La clase debe tener m�todos para
setear la hora de ingreso y de salida para cada d�a
obtener el n�mero total de horas y minutos trabajados en la semana
todo otro m�todo que considere
*/
class Semana_Laboral{
 public:
    Semana_Laboral(int dni, std::string nombre);
    void set_hora_ingreso(int h, int m, int s);
    void set_hora_salida(int h, int m, int s);
    double  horas_totales_semana();


 private:
    std::string nombre;
    int dni;
    int dia;
    Tiempo agenda[2][5];
    
};

Semana_Laboral::Semana_Laboral(int dni, std::string nombre) : dni(dni), nombre(nombre), dia(0){ 
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 2; ++j) {
            agenda[j][i] = Tiempo();
        }
    }
}

void Semana_Laboral :: set_hora_ingreso(int h, int m, int s){
    agenda[0][dia].estableceHora1(h);
    agenda[0][dia].estableceMinuto(m);
    agenda[0][dia].estableceSegundo(s);
}

void Semana_Laboral :: set_hora_salida(int h, int m, int s){
    agenda[1][dia].estableceHora1(h);
    agenda[1][dia].estableceMinuto(m);
    agenda[1][dia].estableceSegundo(s);
    dia = dia<5 ? dia + 1 : 0 ;
}

double Semana_Laboral::horas_totales_semana(){
    double total_horas = 0;  // Variable local, no afecta el estado del objeto
    for (int i = 0; i < 5; i++) {
        total_horas += agenda[1][i].obtieneHora1() + agenda[1][i].obtieneMinuto()*1.0/60 + agenda[1][i].obtieneSegundo()*1.0/3600  - ( agenda[0][i].obtieneHora1()  + agenda[0][i].obtieneMinuto()*1.0/60 + agenda[0][i].obtieneSegundo()*1.0/3600);
    }
    return total_horas;
}


int main(int argc, char *argv[]){
    Semana_Laboral s (43373534, "federico");
    double ht;
    for (int i = 0; i < 5; i++) {
        s.set_hora_ingreso( 8, 0, 0);
        s.set_hora_salida(18, 20, 40);
    }
    ht = s.horas_totales_semana();
    cout << "total horas="<< ht <<endl;

}

