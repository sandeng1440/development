#include <stdio.h>
#include <stdlib.h>

int binarySearch(int, int[], int);
int recursiveBinarySearch(int, int[], int, int);
int *createArr(int);

int main() {
  int *arr = createArr(20);
  int num;
  printf("\nEnter the number to search for in the array of size 20: ");
  scanf("%d", &num);
  int ret = recursiveBinarySearch(num, arr, 0, 19);
  if (ret == -1) {
    printf("%d does not exist in the array", num);
  } else {
    printf("arr[%d]: %d", ret, num);
  }
  main();
  return 0;
}

int recursiveBinarySearch(int target, int arr[], int start, int end) {
  if (end >= start) {
    int mid = start + ((end - start) / 2);
    if (target == arr[mid]) {
      return mid;
    }
    if (target < arr[mid]) {
      return recursiveBinarySearch(target, arr, start, mid - 1);
    }
    return recursiveBinarySearch(target, arr, mid + 1, end);
  }
  return -1;
}

int *createArr(int size) {
  int *arr = (int *)calloc(size, sizeof(int));
  for (int i = 0; i < size; i++) {
    arr[i] = i * 2;
  }
  printf("\nArray created of size %d", size);
  return arr;
}
