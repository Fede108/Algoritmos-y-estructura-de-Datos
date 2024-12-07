// DEITEL pag 631 en adelante
#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;
// La definici?n de la clase Punto3 representa un par de coordenadas x-y.
class Punto3 {

public:
   Punto3( int = 0, int = 0 ); // constructor predeterminado

   void estableceX( int );    // establece x en el par de coordenadas
   int obtieneX() const;      // devuelve x desde el par de coordenadas
   
   void estableceY( int );    // establece y en el par de coordenadas
   int obtieneY() const;      // devuelve y desde el par de coordenadas
   
   void imprime() const;  // muestra el objeto Punto3

private: 
   int x;  // parte x del par de coordenadas
   int y;  // parte y del par de coordenadas

}; // fin de la clase Punto3
// Definici?n de las funciones miembro de Punto3
// constructor predeterminado
Punto3::Punto3( int valorX, int valorY )
   : x( valorX ), y( valorY )
{
   // cuerpo vacio 
   //x=valorX;
   //y=valorY;

} // fin del constructor Punto3 

// establece x en el par de coordenadas
void Punto3::estableceX( int valorX )
{
   x = valorX; // no requiere validaci?n

} // fin de la funci?n estableceX

// devuelve x desde el par de coordenadas
int Punto3::obtieneX() const
{
   return x;

} // fin de la funci?n obtieneX

// establece y en el par de coordenadas
void Punto3::estableceY( int valorY )
{
   y = valorY; // no requiere validaci?n

} // fin de la funci?n estableceY

// devuelve y desde el par de coordenadas
int Punto3::obtieneY() const
{
   return y;

} // fin de la funci?n obtieneY
   
// muestra el objeto Punto3
void Punto3::imprime() const
{
   cout << '[' << obtieneX() << ", " << obtieneY() << ']';

} // fin de la funci?n imprime

// La clase Circulo4 contiene el par de coordenadas x-y y el radio.
class Circulo4 : public Punto3 {

public:

   // constructor predeterminado
   Circulo4( int = 0, int = 0, double = 0.0 );  

   void estableceRadio( double );   // establece el radio
   double obtieneRadio() const;   // devuelve el radio

   double obtieneDiametro() const;       // devuelve el di?metro
   double obtieneCircunferencia() const; // devuelve la circunferencia
   double obtieneArea() const;           // devuelve el ?rea

   void imprime() const;          // muestra el objeto Circulo4

private: 
   double radio;  // radio del Circulo4

}; // fin de la clase Circulo4
// Definici?n de las funciones miembro de Circulo4.
// constructor predeterminado
Circulo4::Circulo4( int valorX, int valorY, double valorRadio )
   : Punto3( valorX, valorY )  // invoca al constructor de la clase base
{
   estableceRadio( valorRadio );

} // fin del constructor Circulo4 

// establece radio 
void Circulo4::estableceRadio( double valorRadio )
{
   radio = ( valorRadio < 0.0 ? 0.0 : valorRadio );

} // fin de la funci?n estableceRadio

// devuelve el radio 
double Circulo4::obtieneRadio() const
{
   return radio;

} // fin de la funci?n obtieneRadio

// calcula y devuelve el di?metro
double Circulo4::obtieneDiametro() const
{
	
   return 2 * obtieneRadio();

} // fin de la funci?n obtieneDiametro

// calcula y devuelve la circunferencia
double Circulo4::obtieneCircunferencia() const
{
   return 3.14159 * obtieneDiametro();

} // fin de la funci?n obtieneCircunferencia

// calcula y devuelve el ?rea
double Circulo4::obtieneArea() const
{
   return 3.14159 * obtieneRadio() * obtieneRadio();

} // fin de la funci?n obtieneArea

// muestra el objeto Circulo4
void Circulo4::imprime() const
{
   cout << "Centro = ";
   Punto3::imprime();      // invoca a la funci?n imprime de Punto3
   cout << "; Radio = " << obtieneRadio();

} // fin de la funci?n imprime

int main(int argc, char *argv[])
{  Circulo4 *circulo; // crea puntero a Circulo4
   Circulo4 xc(10,10,5.75); // crea objeto de tipo Circulo4
   circulo= new Circulo4( 37, 43, 2.5 ); // crea la instancia del objeto Circulo4
   // despliega las coordenadas del punto
   cout << "La coordenada X es " << circulo->obtieneX() 
        << "\nLa coordenada Y es " << circulo->obtieneY()
        << "\nEl radio es " << (*circulo).obtieneRadio();// circulo->obtieneRadio()
    cout<<endl<<endl;    
    cout << "La coordenada X de xc es " << xc.obtieneX() 
        << "\nLa coordenada Y de xc es " << xc.obtieneY()
        << "\nEl radio de xc es " << xc.obtieneRadio();// circulo->obtieneRadio()

   circulo->estableceX( 2 );          // establece la nueva coordenada x
   circulo->estableceY( 2 );          // establece la nueva coordenada y
   circulo->estableceRadio( 4.25 );   // establece el nuevo radio

   // despliega el nuevo valor de c?rculo
   cout << "\n\nLa nueva ubicacion y el radio del circulo es\n";
   circulo->imprime();

   // despliega los valores en punto flotante con 2 d?gitos de precisi?n
   cout << fixed << setprecision( 2 );

   // despliega el di?metro de Circulo4
   cout << "\nEl diametro es " << circulo->obtieneDiametro();

   // despliega la circunferencia de Circulo4
   cout << "\nLa circunferencia es " << circulo->obtieneCircunferencia();

   // despliega el ?rea de Circulo4
   cout << "\nEl area es " << circulo->obtieneArea();

   cout << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}
// Agregar funciones miembro que:
// desplacen el punto un dx y dy
// incremente el circulo un %
// Calcular el perimetro de la semi circunferencia      
