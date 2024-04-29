
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  uint32_t val;
  struct Node *next;
};

int32_t main(int argc, char *argv[]) {

  struct Node *head = malloc(sizeof(struct Node));
  head->val = 46;
  struct Node *current = malloc(sizeof(struct Node));
  current->val = 62;
  head->next = current;

  current = malloc(sizeof(struct Node));
  current->val = 23;
  head->next->next = current;

  printf("%d -> %d -> %d\n", head->val, head->next->val, head->next->next->val);

  return 0;
}
