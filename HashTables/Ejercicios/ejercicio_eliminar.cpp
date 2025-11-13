// ejercicio_eliminar.cpp
// Ejercicio: Eliminar elementos de una tabla hash
#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    std::unordered_map<std::string, int> tablaHash = {
        {"x", 10}, {"y", 20}, {"z", 30}
    };
    std::string clave;
    std::cout << "Introduce la clave a eliminar: ";
    std::cin >> clave;
    tablaHash.erase(clave);
    std::cout << "Elementos restantes en la tabla hash:" << std::endl;
    for (const auto& par : tablaHash) {
        std::cout << par.first << ": " << par.second << std::endl;
    }
    return 0;
}
