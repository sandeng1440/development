#include <iostream>
using namespace std;

int que[100], n = 100, front = -1, rear = -1;
void enqueue();
void dequeue();
void Display();

int main() {
  int ch;
  cout << "1) Insert element to queue" << endl;
  cout << "2) Delete element from queue" << endl;
  cout << "3) Display all the elements on the queue" << endl;
  cout << "4) Exit" << endl;
  do {
    cout << "Enter your choice: " << endl;
    cin >> ch;
    switch (ch) {
    case 1:
      enqueue();
      break;
    case 2:
      dequeue();
      break;
    case 3:
      Display();
      break;
    case 4:
      cout << "Exit" << endl;
      break;
    default:
      cout << "Invalid choice" << endl;
    }
  } while (ch != 4);
  return 0;
}

void enqueue() {
  int val;
  if (rear == n - 1) {
    cout << "Queue Overflow" << endl;
    return;
  }
  if (front == -1) {
    front = 0;
  }
  if (front > -1) {
    cout << "Insert the element in queue: " << endl;
    cin >> val;
    rear++;
    que[rear] = val;
  }
}

void dequeue() {
  if (front == -1 || front > rear) {
    cout << "Queue Overflow" << endl;
  } else {
    cout << "Element deleted from queue is: " << que[front] << endl;
    front++;
  }
}

void Display() {
  if (front == -1) {
    cout << "Queue is empty" << endl;
  } else {
    cout << "Queue elements are: ";
    for (int i = front; i <= rear; i++) {
      cout << que[i] << " -> ";
    }
    cout << "end" << endl;
  }
}
