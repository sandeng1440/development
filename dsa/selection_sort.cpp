#include <array>
#include <iostream>
using namespace std;

array<int, 10> selectionSort(array<int, 10> &);
void selectionSort(int *, int);
void display(array<int, 10>);
void display(int *, int);
array<int, 10> unsortedArr = {9, 1, 3, 0, 5, 6, 4, 8, 7, 2};
int arr[] = {9, 1, 3, 0, 5, 6, 4, 8, 7, 2};
int arr_size = sizeof(arr) / sizeof(int);

int main() {
  display(unsortedArr);
  display(selectionSort(unsortedArr));
  display(arr, arr_size);
  selectionSort(arr, arr_size);
  display(arr, arr_size);
  return 0;
}

void display(array<int, 10> arr) {
  for (int n : arr) {
    cout << n << " -> ";
  }
  cout << "End" << endl;
}
void display(int arr[], int a_len) {
  for (int i = 0; i < a_len; i++) {
    cout << arr[i] << " -> ";
  }
  cout << "End" << endl;
}
array<int, 10> selectionSort(array<int, 10> &arr) {
  int n = arr.size();
  for (int i = 0; i < n - 1; i++) {
    int *min = &arr[i];
    for (int ii = i + 1; ii < n; ii++) {
      if (arr[ii] < *min) {
        min = &arr[ii];
      }
    }
    if (arr[i] != *min) {
      int tmp = arr[i];
      arr[i] = *min;
      *min = tmp;
    }
  }
  return arr;
}

void selectionSort(int arr[], int a_len) {
  for (int i = 0; i < a_len - 1; i++) {
    int *min = &arr[i];
    for (int ii = i; ii < a_len; ii++) {
      if (arr[ii] < *min) {
        min = &arr[ii];
      }
    }
    if (arr[i] != *min) {
      int tmp = arr[i];
      arr[i] = *min;
      *min = tmp;
    }
  }
}
