
#include <iomanip>
#include <iostream>

using namespace std;

struct node {
  int data;
  struct node *next;
};

class stack_llist {
private:
  node *top;

public:
  stack_llist() { top = nullptr; }
  void push(int);
  void pop();
  void traverse();
};

int menu() {
  cout << endl << setw(60) << setfill('-');
  cout << "\n1) Push to stack" << endl;
  cout << "2) Pop from stack" << endl;
  cout << "3) Show stack elements" << endl;
  cout << "4) Quit" << endl;
  int ch;
  cin >> ch;
  return ch;
}

int main() {
  stack_llist stack;
  int choice;
  int val;
  do {
    choice = menu();
    switch (choice) {
    case 1:
      cout << "Enter value: ";
      cin >> val;
      stack.push(val);
      stack.traverse();
      break;
    case 2:
      stack.pop();
      stack.traverse();
      break;
    case 3:
      stack.traverse();
      break;
    default:
      cout << "Exiting...";
    }
  } while (choice != 4);
  return 0;
}

void stack_llist::push(int val) {
  struct node *newNode = new node;
  newNode->data = val;
  if (!top) {
    newNode->next = nullptr;
    top = newNode;
    return;
  }
  newNode->next = top;
  top = newNode;
}

void stack_llist::pop() {
  if (!top) {
    cout << "Stack is empty" << endl;
  } else {
    struct node *tmp = top;
    top = tmp->next;
    free(tmp);
  }
}

void stack_llist::traverse() {
  if (!top) {
    cout << "Stack is empty" << endl;
    return;
  }

  cout << setw(30) << setfill('-') << endl;
  cout << "\nStack Elements: ";
  struct node *curr = top;
  while (curr) {
    cout << curr->data << " -> ";
    curr = curr->next;
  }
  cout << endl << setw(30) << setfill('-') << endl;
}
