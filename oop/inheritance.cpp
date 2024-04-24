#include <iostream>
using namespace std;

class Rectangle {
protected:
  int len, width;
};
class Rec : public Rectangle {
public:
  void Area() {
    cout << "Enter length: " << endl;
    cin >> len;
    cout << "Enter width: " << endl;
    cin >> width;
    cout << "Area = " << len * width;
  }
};

int main() {
  Rec myRectangle;
  myRectangle.Area();
  return 0;
}
