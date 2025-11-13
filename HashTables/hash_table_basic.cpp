// hash_table_basic.cpp
// Ejemplo básico de creación e interacción con una tabla hash en C++
#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    std::unordered_map<std::string, int> tablaHash;

    // Insertar elementos
    tablaHash["uno"] = 1;
    tablaHash["dos"] = 2;
    tablaHash["tres"] = 3;

    // Acceder a un elemento
    std::cout << "El valor de 'dos' es: " << tablaHash["dos"] << std::endl;

    // Modificar un elemento
    tablaHash["dos"] = 22;
    std::cout << "El nuevo valor de 'dos' es: " << tablaHash["dos"] << std::endl;

    // Eliminar un elemento
    tablaHash.erase("uno");

    // Recorrer la tabla hash
    std::cout << "Elementos en la tabla hash:" << std::endl;
    for (const auto& par : tablaHash) {
        std::cout << par.first << ": " << par.second << std::endl;
    }

    // Buscar un elemento
    if (tablaHash.find("tres") != tablaHash.end()) {
        std::cout << "'tres' está en la tabla hash." << std::endl;
    } else {
        std::cout << "'tres' NO está en la tabla hash." << std::endl;
    }

    return 0;
}
