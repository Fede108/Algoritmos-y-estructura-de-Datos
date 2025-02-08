#ifndef VECTOR_H
#define VECTOR_H

using namespace std;

template <typename T> class Vector
{
private:
    T* arreglo;
    int capacidad;
    int actual;
public:
    Vector();
    ~Vector();
    void push(T data);
    T get(int indice);
	void pop() { actual--; }
	int size() { return actual; }
	int getCapacidad() { return capacidad; }
	T* getArray() { return arreglo; }
	void print()
	{
		for (int i = 0; i < actual; i++) {
			cout << arreglo[i] << " ";
		}
		cout << endl;
	}
};


template <typename T> Vector<T>::Vector()
{
    arreglo = new T[1];
	capacidad = 1;
	actual = 0;
}

template <typename T> Vector<T>::~Vector()
{
    delete[] arreglo;
}

template <typename T> void Vector<T>::push(T data){
		if (actual == capacidad) {           // si la cantidad de elementos es igual a la capacidad
			T* temp = new T[2 * capacidad];  // se duplica la capacidad

			for (int i = 0; i < capacidad; i++) {
				temp[i] = arreglo[i];
			}

			delete[] arreglo;
			capacidad *= 2;
			arreglo = temp;
		}

		arreglo[actual] = data;
		actual++;
}

template <typename T> T Vector<T>:: get(int indice)
{
	if (indice < actual)
		return arreglo[indice];
	return NULL;
}

#endif