/****************************************
 *                                       *
 *             SELECTION SORT            *
 *                                       *
 *****************************************/
#include <stdio.h>

void selection_sort(int[], int);
void display(int[], int);

int main() {
  int arr[] = {3, 2, 6, 4, 8, 9, 0, 7, 1, 5};
  int a_len = sizeof(arr) / sizeof(int);
  display(arr, a_len);
  selection_sort(arr, a_len);
  display(arr, a_len);
  return 0;
}

void selection_sort(int arr[], int a_len) {
  for (int i = 0; i < a_len - 1; ++i) {
    int *min = &arr[i];
    for (int ii = i + 1; ii < a_len; ++ii) {
      if (arr[ii] < *min) {
        min = &arr[ii];
      }
    }
    if (arr[i] != *min) {
      int tmp = *min;
      *min = arr[i];
      arr[i] = tmp;
    }
  }
}

void display(int arr[], int a_len) {
  printf("\n[");
  for (int i = 0; i < a_len; ++i) {
    printf(" %d", arr[i]);
  }
  printf(" ]");
}
