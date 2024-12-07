// DEITEL pag 439 en adelante
#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

class Tiempo {

public:
   Tiempo( int = 0, int = 0, int = 0); // constructor predeterminado
   ~Tiempo(); // destructor predeterminado
   // funciones establecer = set
   void estableceHora( int, int, int ); // establece hora, minuto, segundo
   void estableceHora1( int );   // establece hora
   void estableceMinuto( int );  // establece minuto
   void estableceSegundo( int ); // establece segundo

   // funciones obtener = get
   int obtieneHora1();        // obtiene hora
   int obtieneMinuto();       // obtiene minuto
   int obtieneSegundo();      // obtiene segundo

   void imprimeUniversal();         // imprime la hora en formato universal
   void imprimeEstandar();          // imprime la hora en formato estándar
   
   void incrementaSegundos(const int);
   void incrementaMinutos(const int );
   void incrementaHoras(const int);
private:
   int hora;     // 0 - 23 (formato de reloj de 24 horas)
   int minuto;   // 0 - 59
   int segundo;  // 0 - 59

}; // fin de la clase Tiempo

// función constructor para inicializar datos privados;
// llama a la función miembro estableceHora para asignar los valores;
// los valores predeterminados son 0 (vea la definicón de la clase)
Tiempo::Tiempo( int hr, int min, int seg ) 
{ 
   cout<<"\n soy el constructor\n";
   estableceHora( hr, min, seg ); 

} // fin del constructor Tiempo
Tiempo::~Tiempo()
{ cout<<"\n soy el destructor ------------";
}
// establece los valores de hora, minuto y segundo
void Tiempo::estableceHora( int h, int m, int s ) 
{ 
   estableceHora1( h );
   estableceMinuto( m );
   estableceSegundo( s );

} // fin de la función estableceHora

// establece el valor de hora
void Tiempo::estableceHora1( int h ) 
{
   hora = ( h >= 0 && h < 24 ) ? h : 0; 

} // fin de la función estableceHora1

// establece el valor de minuto
void Tiempo::estableceMinuto( int m )
{ 
   minuto = ( m >= 0 && m < 60 ) ? m : 0; 

} // fin de la función estableceMinuto

// establece el valor de segundo
void Tiempo::estableceSegundo( int s )
{ 
   segundo = ( s >= 0 && s < 60 ) ? s : 0; 

} // fin de la función estableceSegundo

// devuelve el valor de hora
int Tiempo::obtieneHora1() 
{ 
   return hora; 

} // fin de la función obtieneHora1

// devuelve el valor de minuto 
int Tiempo::obtieneMinuto() 
{
   return minuto; 

} // fin de la función obtieneMinuto

// devuelve el valor de segundo 
int Tiempo::obtieneSegundo() 
{ 
   return segundo;
   
} // fin de la función obtieneSegundo

// imprime Tiempo en formato universal
void Tiempo::imprimeUniversal()
{
   cout << setfill( '0' ) << setw( 2 ) << hora << ":"
        << setw( 2 ) << minuto << ":"
        << setw( 2 ) << segundo;

} // fin de la función imprimeUniversal

// print Time in standard format
// imprime Tiempo en formato estándar
void Tiempo::imprimeEstandar()
{
   cout << ( ( hora == 0 || hora == 12 ) ? 12 : hora % 12 )
        << ":" << setfill( '0' ) << setw( 2 ) << minuto
        << ":" << setw( 2 ) << segundo 
        << ( hora < 12 ? " AM" : " PM" );

} // fin de la funcion imprimeEstandar
void Tiempo::incrementaSegundos(const int cuenta )
{
   cout << "Incrementa segundo " << cuenta
        << " veces:\nHora inicio: ";
   imprimeEstandar();

   for ( int i = 0; i < cuenta; i++ ) {
      estableceSegundo( ( obtieneSegundo() + 1 ) % 60 );  

      if ( obtieneSegundo() == 0 )
         incrementaMinutos(1);

      cout << "\nsegundo + 1: ";
      imprimeEstandar();

   } // fin de for

   cout << endl;

} // fin de la función incrementaSegundos

void Tiempo::incrementaMinutos(const int cuenta )
{
   cout << "Incrementa minuto " << cuenta
        << " veces:\nHora inicio: ";
   imprimeEstandar();

   for ( int i = 0; i < cuenta; i++ ) {
      estableceMinuto( ( obtieneMinuto() + 1 ) % 60 );  

      if ( obtieneMinuto() == 0 )
         incrementaHoras(1);

      cout << "\nminuto + 1: ";
      imprimeEstandar();

   } // fin de for

   cout << endl;

} // fin de la función incrementaMinutos

void Tiempo::incrementaHoras(const int cuenta )
{
   cout << "Incrementa hora " << cuenta
        << " veces:\nHora inicio: ";
   imprimeEstandar();

   for ( int i = 0; i < cuenta; i++ ) {
      estableceHora1( ( obtieneHora1() + 1 ) % 24 );

      cout << "\nhora + 1: ";
      imprimeEstandar();

   } // fin de for

   cout << endl;

} // fin de la función incrementaHoras

int main(int argc, char *argv[])
{  
    {Tiempo t(14,40,0),x,y(10);              // crea el objeto de Tiempo
      t.imprimeEstandar(); cout<<endl;
      x.imprimeEstandar(); cout<<endl;
      y.imprimeEstandar(); cout<<endl;
    
      //Tiempo *p= new Tiempo(11,11,11);
      //p->imprimeEstandar();cout<<endl;
      
   // establece la hora mediante funciones establece (set) individuales
   t.estableceHora1( 17 );     // establece hora en un valor válido
   t.estableceMinuto( 34 );   // establece minuto en un valor válido
   t.estableceSegundo( 25 );   // establece segundo en un valor válido

   // funciones obtener (get) para obtener hora, minuto y segundo
   cout << "Resultado de establecer todos los valores validos:\n" 
        << "  Hora: " << t.obtieneHora1()
        << "  Minuto: " << t.obtieneMinuto()
        << "  Segundo: " << t.obtieneSegundo();

   // establece hora mediante el uso de funciones individuales
   t.estableceHora1( 234 );     // establece hora no válida en 0
   t.estableceMinuto( 43 );    // establece minuto en un valor válido
   t.estableceSegundo( 6373 ); // establece segundo no válido en 0

   // despliega hora, minuto y segundo después de establecer 
   // los valores no válidos de hora y segundo
   cout << "\n\nResultado del intento de establecer los valores no validos de minuto"
        << " y segundo:\n  Hora: " << t.obtieneHora1()
        << "  Minuto: " << t.obtieneMinuto()
        << "  Segundo: " << t.obtieneSegundo() << "\n\n";

   t.estableceHora( 11, 58, 0 );    // establece hora
   t.incrementaSegundos( 150 );  // incrementa los minutos de t en 3
   t.imprimeEstandar(); cout<<endl;



    cout<<endl<<endl;

  }
    cout<<endl<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}

/*
Hacer una clase Semana_Laboral
que almacene:
el Nombre de un empleado
su documento
en un arreglo de 5 x 2 de tipo Tiempo la hora de ingreso y de salida de cada día
La clase debe tener métodos para
setear la hora de ingreso y de salida para cada día
obtener el número total de horas y minutos trabajados en la semana
todo otro método que considere
*/



