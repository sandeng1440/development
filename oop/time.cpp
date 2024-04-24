#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;

class Rectangle {
private:
  int l;
  float w;

public:
  void Get() {
    time_t N = time(0);
    char *T = ctime(&N);
    ofstream out;
    out.open("/home/santiago/Documents/Devel/oop", ios::app);
    cout << "Enter length and width" << endl;
    cin >> l >> w;
    cout << l << "x" << w << "=" << (l * w) << endl;
    cout << "Transaction has been posted" << endl;
    out.close();
  }
};
int main() {
  Rectangle myRect;
  myRect.Get();
  return 0;
}
