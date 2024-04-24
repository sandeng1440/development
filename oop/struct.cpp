#include <iostream>
using namespace std;

struct Rectangle {
  int length;
  float width;

  void Get() {
    cout << "Enter length and width:" << endl;
    cin >> length >> width;
    cout << "Area = " << (width * length) << endl;
  }
} R;
int main() {
  R.Get();
  return 0;
}
