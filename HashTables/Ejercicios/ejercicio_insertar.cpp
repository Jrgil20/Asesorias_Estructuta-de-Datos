// ejercicio_insertar.cpp
// Ejercicio: Insertar elementos en una tabla hash y mostrarlos
#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    std::unordered_map<std::string, int> tablaHash;
    int n;
    std::string clave;
    int valor;

    std::cout << "¿Cuántos elementos deseas insertar? ";
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cout << "Clave: ";
        std::cin >> clave;
        std::cout << "Valor: ";
        std::cin >> valor;
        tablaHash[clave] = valor;
    }
    std::cout << "Elementos en la tabla hash:" << std::endl;
    for (const auto& par : tablaHash) {
        std::cout << par.first << ": " << par.second << std::endl;
    }
    return 0;
}
