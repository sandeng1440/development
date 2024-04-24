#include <iostream>
using namespace std;

void bubbleSort(int[], int);
void display(int[], int);

int main() {
  int arr[] = {9, 1, 3, 0, 5, 6, 4, 8, 7, 2};
  int size = sizeof(arr) / sizeof(int);
  display(arr, size);
  bubbleSort(arr, size);
  display(arr, size);
  return 0;
}
void bubbleSort(int arr[], int n) {
  for (int i = 0; i < n; i++) {
    for (int ii = 1; ii < n - i; ii++) {
      if (arr[ii] < arr[ii - 1]) {
        int tmp = arr[ii];
        arr[ii] = arr[ii - 1];
        arr[ii - 1] = tmp;
      }
    }
  }
}
void display(int arr[], int n) {
  cout << "[ ";
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  cout << "]" << endl;
}
