// dispersion_modulo.cpp
// Ejemplo interactivo de dispersión por módulo Zn en C++
// Este programa simula una tabla hash simple usando la función de dispersión "módulo n".
// Los datos se agrupan en cubetas según su residuo al dividir entre n (n = número de cubetas).

#include <iostream>
#include <vector>

int main() {
    int nCubetas;      // Número de cubetas (Zn)
    int nElementos;    // Cantidad de números a ingresar

    // Solicita al usuario el número de cubetas (Zn)
    std::cout << "¿En cuántas cubetas (Zn) quieres dispersar los datos? ";
    std::cin >> nCubetas;
    std::vector<std::vector<int>> cubetas(nCubetas); // Vector de cubetas

    // Solicita la cantidad de números a ingresar
    std::cout << "¿Cuántos números deseas ingresar? ";
    std::cin >> nElementos;
    std::cout << "Ingresa los números:\n";

    // Lee los números y los asigna a la cubeta correspondiente según su residuo
    for (int i = 0; i < nElementos; ++i) {
        int num;
        std::cin >> num;
        int indice = num % nCubetas; // Función de dispersión: módulo n
        cubetas[indice].push_back(num);
    }

    // Muestra el contenido de cada cubeta
    std::cout << "\nContenido de las cubetas (por módulo " << nCubetas << "):\n";
    for (int i = 0; i < nCubetas; ++i) {
        std::cout << "Cubeta " << i << ": ";
        for (int num : cubetas[i]) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
