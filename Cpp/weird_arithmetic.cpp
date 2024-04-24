#include <iostream>
#include <string>
using namespace std;

int main() {
  double a = 0.1;
  double b = 0.2;
  double c = 0.1 + 0.2;
  cout << "a + b = " << a + b << endl;
  cout << "0.1 + 0.2 = " << c << endl;
  bool t = 0.1 + 0.2 == 0.3;
  string tr = t ? "True" : "False";
  cout << "0.1 + 0.2 == 0.3 : " << tr << endl;
}
