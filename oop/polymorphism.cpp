#include <iostream>
using namespace std;

class compute {
private:
  int x;
  float y;

public:
  void get() {
    cout << "Enter an integer: " << endl;
    cin >> x;
    cout << "Enter a real number: " << endl;
    cin >> y;
    manip(x);
    manip(y);
    manip(x, y);
  }

public:
  void manip(int a, float b) { cout << "Product = " << (a * b) << endl; }
  void manip(int a) { cout << "Square = " << (a * a) << endl; }
  void manip(float b) { cout << "Real = " << b << endl; }
};

int main() {
  compute c;
  c.get();
  return 0;
}
