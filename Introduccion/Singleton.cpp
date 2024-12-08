#include <iostream>
class Singleton {
private:
    Singleton() {}
    ~Singleton() {}
    Singleton(const Singleton&) = delete;           // Prohíbe el constructor por copia
    Singleton& operator=(const Singleton&) = delete; // Prohíbe el operador de asignación

    static Singleton *instance;

public:
    static Singleton *Instance() {
        if (!instance) {
            instance = new Singleton();
        }
        return instance;
    }
};

Singleton *Singleton::instance = 0;

int main() {
    Singleton *minstance = Singleton::Instance();
    std::cout << "Instance: " << minstance << std::endl;

    // Las siguientes líneas causarían errores en compilación
    // Singleton copia(*minstance); // No permitido
    // Singleton copia2 = *minstance; // No permitido

    return 0;
}
