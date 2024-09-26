#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    // Entrada y salida estándar
    int num;
    std::cout << "Ingrese un número: ";
    std::cin >> num;
    std::cout << "El número ingresado es: " << num << std::endl;

    // Entrada y salida de archivos
    std::ofstream archivoSalida("datos.txt");
    archivoSalida << "Este es un ejemplo de salida a un archivo." << std::endl;
    archivoSalida.close();

    std::ifstream archivoEntrada("datos.txt");
    std::string linea;
    while (std::getline(archivoEntrada, linea)) {
        std::cout << linea << std::endl;
    }
    archivoEntrada.close();

    // Entrada y salida de cadenas de texto
    std::stringstream cadena;
    cadena << "Este es un ejemplo de salida a una cadena de texto." << std::endl;
    std::string resultado = cadena.str();
    std::cout << resultado;

    return 0;
}