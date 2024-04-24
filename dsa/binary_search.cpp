#include <iostream>
using namespace std;

bool recursive_binary_search(int, int[], int);
int *create_sorted_array(int);

int main() {
  int size = 0;
  cout << "Enter the size of array to create: ";
  cin >> size;
  int *arr = create_sorted_array(size);
  int target;
  cout << "\nEnter the number to search: ";
  cin >> target;
  cout << "\n"
       << target << " Found: " << recursive_binary_search(target, arr, size)
       << endl;
  return 0;
}

bool recursive_binary_search(int target, int arr[], int a_len) {
  if (a_len == 0) {
    return false;
  }

  int mid = a_len / 2;
  if (arr[mid - 1] == target) {
    return true;
  }
  if (target < arr[mid - 1]) {
    int *arr_2 = (int *)calloc(mid, sizeof(int));
    for (int i = 0; i < mid; i++) {
      arr_2[i] = arr[i];
    }
    return recursive_binary_search(target, arr_2, mid);
  }
  if (target > arr[mid - 1]) {
    int a2_len = a_len - mid + 1;
    int *arr_2 = (int *)calloc(a2_len, sizeof(int));
    for (int i = 0; i < a2_len; i++) {
      arr_2[i] = arr[a2_len + i];
    }
    return recursive_binary_search(target, arr_2, a2_len);
  }
  return false;
}

int *create_sorted_array(int n) {
  int *arr = (int *)calloc(n, sizeof(int));
  for (int i = 0; i < n; i++) {
    arr[i] = i;
  }
  return arr;
}
