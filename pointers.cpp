#include <iostream>

using namespace std;

int main() {
  int var = 20; // Variable declarada
  int *ip; // Puntero declarado

  ip = &var; // Dirección de var asignada a ip

  cout << "Valor de var: " << var << endl;
  cout << "Dirección de var: " << &var << endl;
  cout << "Valor de ip (dirección de var): " << ip << endl;
  cout << "Valor al que apunta ip: " << *ip << endl;

  return 0;
}
