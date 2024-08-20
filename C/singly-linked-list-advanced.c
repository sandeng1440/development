#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  uint32_t val;
  struct Node *next;
};

void display(struct Node *head) {
  struct Node *current = head;
  while (current != NULL) {
    printf("%d -> ", current->val);
    current = current->next;
  }
  printf("NULL\n");
}

struct Node *createNode(int val) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->val = val;
  newNode->next = NULL;
  return newNode;
}
void insertLast(struct Node *head, int val) {
  struct Node *newNode = createNode(val);
  struct Node *current = head;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = newNode;
}

struct Node *insertFirst(struct Node *head, int val) {
  if (head == NULL) {
    struct Node *newNode = createNode(val);
    head = newNode;
    return head;
  } else {
    struct Node *newNode = createNode(val);
    newNode->next = head;
    head = newNode;
    return head;
  }
}

int main() {
  struct Node *List = createNode(6);
  insertLast(List, 420);
  insertLast(List, 10);
  insertLast(List, 45);
  List = insertFirst(List, 2);
  List = insertFirst(List, 1111);

  display(List);

  return 0;
}
