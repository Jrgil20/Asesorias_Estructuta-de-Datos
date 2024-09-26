// Suggested code may be subject to a license. Learn more: ~LicenseLog:1677528676.
#include <iostream>

int factorial(int n) {
  if (n == 0) {
    return 1;
  } else {
    return n * factorial(n - 1);
  }
}

int main() {
  int n = 5;
  int result = factorial(n);
  std::cout << "El factorial de " << n << " es: " << result << std::endl;
  return 0;
}
