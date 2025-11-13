// ejercicio_buscar.cpp
// Ejercicio: Buscar elementos en una tabla hash
#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    std::unordered_map<std::string, int> tablaHash = {
        {"a", 1}, {"b", 2}, {"c", 3}
    };
    std::string clave;
    std::cout << "Introduce la clave a buscar: ";
    std::cin >> clave;
    if (tablaHash.find(clave) != tablaHash.end()) {
        std::cout << "Valor: " << tablaHash[clave] << std::endl;
    } else {
        std::cout << "La clave no existe en la tabla hash." << std::endl;
    }
    return 0;
}
