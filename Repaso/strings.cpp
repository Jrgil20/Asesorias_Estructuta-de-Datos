#include <iostream>
#include <string>

using namespace std;

int main() {
  string myString = "Hello";
  string yourString = "World";

  cout << "My string is: " << myString << endl;
  cout << "Your string is: " << yourString << endl;

  string combinedString = myString + " " + yourString;
  cout << "Combined string: " << combinedString << endl;

  if (myString == yourString) {
    cout << "Strings are equal" << endl;
  } else {
    cout << "Strings are not equal" << endl;
  }

  return 0;
}
