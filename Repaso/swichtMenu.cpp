#include <iostream>

int main() {
    int opcion;

    std::cout << "Menu:" << std::endl;
    std::cout << "1. Opción 1" << std::endl;
    std::cout << "2. Opción 2" << std::endl;
    std::cout << "3. Opción 3" << std::endl;
    std::cout << "Ingrese una opción: ";
    std::cin >> opcion;

    switch (opcion) {
        case 1:
            std::cout << "Ha seleccionado la opción 1." << std::endl;
            break;
        case 2:
            std::cout << "Ha seleccionado la opción 2." << std::endl;
            break;
        case 3:
            std::cout << "Ha seleccionado la opción 3." << std::endl;
            break;
        default:
            std::cout << "Opción inválida." << std::endl;
            break;
    }

    return 0;
}