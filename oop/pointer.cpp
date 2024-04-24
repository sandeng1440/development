#include <iostream>
using namespace std;

class pointer {
private:
  int *p;
  int l;

public:
  void work() {
    p = &l;
    l = 15000;
    cout << "Enter some value through pointer:" << endl;
    cin >> *p;
    cout << "Value of l = " << *p << endl;
  }
};
int main() {
  pointer my_pointer;
  my_pointer.work();

  return 0;
}
