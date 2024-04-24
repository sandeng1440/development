#include <iostream> // Header file
using namespace std;

class Number { // Class definition
private:
  int x;

public:
  void show() {
    cout << "Enter the number: " << endl;
    cin >> x;
    cout << "Number = " << x << endl;
  }
};

int main() {    // Main function
  Number myNum; // Class instantiation
  myNum.show();
  return 0;
}
