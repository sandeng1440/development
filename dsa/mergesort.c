#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void merge_sort(int32_t[], int32_t);
void merge(int32_t[], int32_t, int32_t[], int32_t, int32_t[], int32_t);
void display(int32_t[], int32_t);

int32_t main() {
  int32_t a[] = {9, 4, 6, 3, 2, 7, 0, 1, 8, 5};
  int32_t size = sizeof(a) / sizeof(int32_t);
  display(a, size);

  merge_sort(a, size);
  display(a, size);
  return 0;
}

void merge_sort(int32_t a[], int32_t a_len) {
  if (a_len <= 1) {
    return;
  }

  int32_t mid = a_len / 2;
  int32_t *left = (int32_t *)malloc(sizeof(int32_t) * mid);
  int32_t *right = (int32_t *)malloc(sizeof(int32_t) * (a_len - mid));

  int32_t l = 0, r = 0;
  for (uint32_t i = 0; i < a_len; ++i) {
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

void merge(int32_t left[], int32_t l_len, int32_t right[], int32_t r_len,
           int32_t a[], int32_t a_len) {
  uint32_t l = 0, r = 0, i = 0;
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

void display(int32_t arr[], int32_t arr_len) {
  // printf("\nsize: %d", arr_len);
  printf("\n[ ");
  for (uint32_t i = 0; i < arr_len; ++i) {
    printf("%d ", arr[i]);
  }
  printf("]\n");
}
