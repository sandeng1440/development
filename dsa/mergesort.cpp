#include <iostream>
using namespace std;

void merge_sort(int[], int);
void merge(int[], int[], int[], int, int, int);
void display(int[], int);

int main() {
  int arr[] = {29, 11, 3,  12, 0,  4,  20, 8,  6,  19, 18, 2,
               1,  16, 14, 5,  15, 13, 9,  17, 16, 19, 7};
  int a_len = sizeof(arr) / sizeof(int);
  display(arr, a_len);
  merge_sort(arr, a_len);
  display(arr, a_len);
  return 0;
}

void merge_sort(int a[], int a_len) {
  // base case
  if (a_len <= 1)
    return;

  int mid = a_len / 2;
  int *left = new int[mid];
  int *right = new int[a_len - mid];

  for (int i = 0, l = 0, r = 0; i < a_len; ++i) {
    if (i < mid) {
      left[l] = a[i];
      ++l;
    } else {
      right[r] = a[i];
      ++r;
    }
  }

  merge_sort(left, mid);
  merge_sort(right, a_len - mid);
  merge(left, right, a, mid, a_len - mid, a_len);
}

void merge(int left[], int right[], int a[], int l_len, int r_len, int a_len) {
  int l = 0, r = 0, i = 0;
  while (l < l_len && r < r_len) {
    if (left[l] < right[r]) {
      a[i] = left[l];
      ++i;
      ++l;
    } else {
      a[i] = right[r];
      ++i;
      ++r;
    }
  }
  while (l < l_len) {
    a[i] = left[l];
    ++i;
    ++l;
  }
  while (r < r_len) {
    a[i] = right[r];
    ++i;
    ++r;
  }
}

void display(int arr[], int a_len) {
  cout << "\n[ ";
  for (int i = 0; i < a_len; ++i) {
    cout << arr[i] << " ";
  }
  cout << "]";
}
