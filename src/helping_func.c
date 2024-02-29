#include "calculus.h"

int isoperator(char *c) {
  if (c == NULL) {
    return 0;
  }
  if (*c == '+' || *c == '-' || *c == '*' || *c == '/') {
    return 1;
  }
  return 0;
}

int ishigher(char *c, char *top) {
  if (top == NULL || c == NULL) {
    return 0;
  }
  char temp1[255], temp2[255];
  strncpy(temp1, c, 1);
  strcpy(temp2, top);
  printf("temp1 = %s\n", temp1);
  printf("temp2 = %s\n", temp2);
  if (!strcmp(temp1, "/") || !strcmp(temp1, "*")) {
    if (!strcmp(temp2, "+") || !strcmp(temp2, "-")) {
      return 1;
    }
  }
  return 0;
}

int queue_to_string(Queue *queue, char *string) {
  if (queue == NULL || string == NULL) {
    return 0;
  }
  while (!isQueueEmpty(queue)) {
    char temp[255];
    strcpy(temp, dequeue(queue));
    strncat(string, temp, 255);
    if (!isQueueEmpty(queue)) {
      strncat(string, " ", 255);
    }
  }
  return 0;
}

int peek_compare(Stack *stack, char *string) {
  if (stack == NULL || string == NULL || isStackEmpty(stack)) {
    return 0;
  }
  char temp[255];
  strcpy(temp, peek(stack));
  return !strcmp(temp, string);
}