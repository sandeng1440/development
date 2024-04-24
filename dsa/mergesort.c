#include <stdio.h>
#include <stdlib.h>

void merge_sort(int[], int);
void merge(int[], int, int[], int, int[], int);
void display(int[], int);

int main() {
  int a[] = {9, 4, 6, 3, 2, 7, 0, 1, 8, 5};
  int size = sizeof(a) / sizeof(int);
  display(a, size);

  merge_sort(a, size);
  display(a, size);
  return 0;
}

void merge_sort(int a[], int a_len) {
  if (a_len <= 1) {
    return;
  }

  int mid = a_len / 2;
  int *left = (int *)malloc(sizeof(int) * mid);
  int *right = (int *)malloc(sizeof(int) * (a_len - mid));

  int l = 0, r = 0;
  for (int i = 0; i < a_len; ++i) {
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
  merge(left, mid, right, a_len - mid, a, a_len);
}

void merge(int left[], int l_len, int right[], int r_len, int a[], int a_len) {
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

void display(int arr[], int arr_len) {
  // printf("\nsize: %d", arr_len);
  printf("\n[ ");
  for (int i = 0; i < arr_len; ++i) {
    printf("%d ", arr[i]);
  }
  printf("]\n");
}
