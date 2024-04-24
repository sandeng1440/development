#include <iostream>
using namespace std;

typedef struct Node {
  int val;
  Node *next;

  Node() { next = nullptr; }
  ~Node() { cout << "A Node has been destroyed" << endl; }
} Node;

typedef struct LList {
  Node *head;

  LList() { head = nullptr; }

  void display() {
    Node *current = head;
    while (current != nullptr) {
      cout << current->val << " -> ";
      current = current->next;
    }
    cout << "NULL" << endl;
  }
  void insertFirst(int val) {
    if (head == nullptr) {
      Node *newNode = new Node;
      newNode->val = val;
      head = newNode;
    } else {
      Node *newNode = new Node;
      newNode->next = head;
      newNode->val = val;
      head = newNode;
    }
  }
  void insertLast(int val) {
    if (head == nullptr) {
      head = new Node;
      head->val = val;
      head->next = nullptr;
    } else {
      Node *newNode = new Node;
      newNode->val = val;
      Node *current = head;
      while (current->next != NULL) {
        current = current->next;
      }
      current->next = newNode;
    }
  }
  ~LList() { cout << "A LList has been destroyed" << endl; }

}LList;

int main() {
  LList myList;
  myList.insertLast(39);
  myList.insertFirst(4);
  myList.insertFirst(3);
  myList.insertFirst(1);
  myList.display();
  return 0;
}
