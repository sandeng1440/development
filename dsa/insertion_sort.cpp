#include <iostream>
using namespace std;

void insertionSort(int[], int);
void display(int[], int);

int main() {
  int arr[] = {9, 1, 3, 0, 5, 6, 4, 8, 7, 2};
  int len = sizeof(arr) / sizeof(int);
  display(arr, len);
  insertionSort(arr, len);
  display(arr, len);
  return 0;
}

void insertionSort(int arr[], int len) {
  for (int i = 1; i < len; i++) {
    for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
      int temp = arr[j];
      arr[j] = arr[j - 1];
      arr[j - 1] = temp;
    }
  }
}
void display(int arr[], int len) {
  cout << "[ ";
  for (int i = 0; i < len; i++) {
    cout << arr[i] << " ";
  }
  cout << "]" << endl;
}
