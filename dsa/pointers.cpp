#include <iostream>
using namespace std;

void ptr_func(int *);

int main() {
  int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int s = sizeof(arr);
  cout << "sizeof(arr): " << s << "\n";
  ptr_func(arr);
}

void ptr_func(int *arr) {
  int s = sizeof(arr);
  int sp = sizeof(*arr);
  int ss = 0;
  int i = 0;
  while (arr[i] != '\0') {
    ++ss;
    ++i;
  }
  cout << "Inside...\n";
  cout << "sizeof(arr) : " << s << "\n";
  cout << "sizeof(*arr): " << sp << "\n";
  cout << "size from while: " << ss << "\n";
}
