#include <iostream>
#include <iterator>
#include <list>

using namespace std;

void showList(list<int> g) {
  list<int>::iterator it;
  for (it = g.begin(); it != g.end(); it++) {
    cout << *it << " -> ";
  }
  cout << "End" << endl;
}

int main() {
  list<int> list1, list2;
  for (int i = 0; i < 10; i++) {
    list1.push_back(i * 2);
    list2.push_front(i * 3);
  }
  cout << "list1 is: ";
  showList(list1);
  cout << "list2 is: ";
  showList(list2);
  cout << "list1.front(): " << list1.front() << endl;
  cout << "list1.back(): " << list1.back() << endl;
  cout << "list1.pop_back(): ";
  list1.pop_back();
  showList(list1);
  return 0;
}
