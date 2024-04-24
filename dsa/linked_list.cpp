#include <iostream>
using namespace std;

struct Node {
  int data;
  Node *next;
};

class s_linked_list {
private:
  Node *head, *tail;

public:
  s_linked_list() {
    head = nullptr;
    tail = nullptr;
  }
  void add_node_front(int n) {
    Node *tmp = new Node;
    tmp->data = n;
    tmp->next = nullptr;

    if (head == nullptr) {
      head = tmp;
      tail = tmp;
    } else {
      tail->next = tmp;
      tail = tail->next;
    }
  }
};

int main() {
  s_linked_list a;
  a.add_node_front(1);
  a.add_node_front(2);
  a.add_node_front(34);
  cout << endl;
  return 0;
}
