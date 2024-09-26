#include <iostream>

int main() {
    for (int i = 0; i < 10; i++) {
        std::cout << "El valor de i es: " << i << std::endl;
    }

    for (int i = 0; i < 10; i += 2) {
        std::cout << "El valor de i es: " << i << std::endl;
    }

    for (int i = 1; i <= 10; i *= 2) {
        std::cout << "El valor de i es: " << i << std::endl;
    }

        return 0;
}