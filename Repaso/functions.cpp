#include <iostream>

// Función por valor (copia el valor del argumento)
void funcionPorValor(int x) {
    x = x + 10;
    std::cout << "Valor dentro de la funcionPorValor: " << x << std::endl;
}

// Función por referencia (modifica el valor original)
void funcionPorReferencia(int &x) {
    x = x + 10;
    std::cout << "Valor dentro de la funcionPorReferencia: " << x << std::endl;
}

// Función que devuelve un valor
int funcionQueDevuelveValor(int a, int b) {
    return a + b;
}

// Función que no devuelve nada (void)
void funcionQueNoDevuelveNada() {
    std::cout << "Mensaje desde funcionQueNoDevuelveNada" << std::endl;
}

int main() {
    int valor = 5;

    funcionPorValor(valor);
    std::cout << "Valor despues de funcionPorValor: " << valor << std::endl;

    funcionPorReferencia(valor);
    std::cout << "Valor despues de funcionPorReferencia: " << valor << std::endl;

    int resultado = funcionQueDevuelveValor(5, 3);
    std::cout << "Resultado de funcionQueDevuelveValor: " << resultado << std::endl;

    funcionQueNoDevuelveNada();

    return 0;
}
