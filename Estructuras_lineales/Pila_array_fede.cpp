template <class T> class Pila{
      private:
            T arreglo[];
      public:
             Pila(){};
             void apilar(T d){this->add(d);};
             T tope(void){return this->cabeza();};
             void desapilar(void){this->borrar();};
             bool pilavacia(){return this->esvacia();};
             void add(T d); //sumar elementos al arreglo
             bool esvacia(void);
             T cabeza(void); //retorna el dato del primer elemento del arreglo
             void borrar(void); //borra la cabeza
};     

template <class T> void Pila<T>:: add(T d){
    for ( i = 0; i < ; i++)
    {
                                
    }
    
    d = arreglo[i]
}