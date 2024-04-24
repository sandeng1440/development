#include <iostream>
using namespace std;

int fibonacci(int);

int main() {
  while (true) {
    int k = 0;
    cout << "\nEnter the number: ";
    cin >> k;
    int r = fibonacci(k);
    cout << "r: " << r << endl;
  }
}

int fibonacci(int x) {
  if (x <= 1) {
    return x;
  }
  return fibonacci(x - 1) + fibonacci(x - 2);
}
