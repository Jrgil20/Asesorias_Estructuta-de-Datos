#include <iostream>

int main() {
    
    int a = 10, b = 5;

    std::cout << "Suma: " << a + b << std::endl;
    std::cout << "Resta: " << a - b << std::endl;
    std::cout << "Multiplicacion: " << a * b << std::endl;
    std::cout << "Division: " << a / b << std::endl;
    std::cout << "Modulo: " << a % b << std::endl;


    bool x = true, y = false;

    std::cout << "AND: " << (x && y) << std::endl;
    std::cout << "OR: " << (x || y) << std::endl;
    std::cout << "NOT x: " << (!x) << std::endl;
    std::cout << "NOT y: " << (!y) << std::endl;


    return 0;
}
