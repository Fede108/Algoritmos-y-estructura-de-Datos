// Self implementation of
// the Vector Class in C++
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
    Vector(/* args */);
    ~Vector();
    void push(T data);
    T get(int indice);
    // function to delete last element
	void pop() { actual--; }

	// function to get size of the vector
	int size() { return actual; }

	// function to get capacity of the vector
	int getcapacity() { return capacidad; }

	// function to print array elements
	void print()
	{
		for (int i = 0; i < actual; i++) {
			cout << arreglo[i] << " ";
		}
		cout << endl;
	}
};


template <typename T> Vector<T>::Vector(/* args */)
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
        // if the number of elements is equal to the
		// capacity, that means we don't have space to
		// accommodate more elements. We need to double the
		// capacity
		if (actual == capacidad) {
			T* temp = new T[2 * capacidad];

			// copying old array elements to new array
			for (int i = 0; i < capacidad; i++) {
				temp[i] = arreglo[i];
			}

			// deleting previous array
			delete[] arreglo;
			capacidad *= 2;
			arreglo = temp;
		}

		// Inserting data
		arreglo[actual] = data;
		actual++;
}

// function to extract element at any index
template <typename T> T Vector<T>:: get(int indice)
{
	// if index is within the range
	if (indice < actual)
		return arreglo[indice];
	// if index is not within range
	return NULL;
}

#endif