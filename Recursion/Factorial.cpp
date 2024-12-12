//Función Recursiva Convencional
int factorial(int n) {
    if (n == 0) {
        return 1; // Caso base
    }
    return n * factorial(n - 1); // La multiplicación ocurre después de la llamada recursiva
}

//Función Recursiva de Cola
int factorial_tail(int n, int acumulador = 1) {
    if (n == 0) {
        return acumulador; // Caso base: el resultado está en el acumulador
    }
    return factorial_tail(n - 1, acumulador * n); // La llamada recursiva es la última operación
}

//Transformación a Iterativo
int factorial_iterativo(int n) {
    int acumulador = 1;
    while (n > 0) {
        acumulador *= n; // Realiza el cálculo intermedio
        n--;             // Decrementa el contador
    }
    return acumulador;
}
