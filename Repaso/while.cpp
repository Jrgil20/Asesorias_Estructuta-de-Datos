#include <iostream>

using namespace std;

int main() {
  int i = 0;
  while (i < 10) {
    if (i == 5) {
      i++;
      continue; 
    }
    if (i == 8) {
      break; 
    }
    cout << i << " ";
    i++;
  }
  cout << endl;
  return 0;
}
