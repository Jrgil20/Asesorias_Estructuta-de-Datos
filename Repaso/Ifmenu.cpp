#include <iostream>

int main() {
    int opcion;

    std::cout << "Menu:" << std::endl;
    std::cout << "1. Opción 1" << std::endl;
    std::cout << "2. Opción 2" << std::endl;
    std::cout << "3. Opción 3" << std::endl;
    std::cout << "Ingrese una opción: ";
    std::cin >> opcion;

    if (opcion == 1) {
        std::cout << "Ha seleccionado la opción 1." << std::endl;
    } else if (opcion == 2) {
        std::cout << "Ha seleccionado la opción 2." << std::endl;
    } else if (opcion == 3) {
        std::cout << "Ha seleccionado la opción 3." << std::endl;
    } else {
        std::cout << "Opción inválida." << std::endl;
    }

    return 0;
}