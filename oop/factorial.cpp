#include <iostream>
using namespace std;

void factorial(int x) {
  if (x == 0) {
    cout << 1 << " ";
    return;
  }
  x *factorial(x - 1);
}

int main() {
  cout << "Enter the num: ";
  int t;
  cin >> t;
  factorial(t);
  return 0;
}
