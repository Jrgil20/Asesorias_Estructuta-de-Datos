#include <iostream>

using namespace std;

int main() {
  int edades[5] = {20, 25, 30, 35, 40};

  cout << "La edad en la posicion 0 es: " << edades[0] << endl;

  for (int i = 0; i < 5; i++) {
    cout << "Edad en la posicion " << i << ": " << edades[i] << endl;
  }

  return 0;
}
