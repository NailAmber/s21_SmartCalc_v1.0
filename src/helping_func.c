#include "calculus.h"

int isoperator(char *c) {
  if (c == NULL) {
    return 0;
  }
  if (*c == '+' || *c == '-' || *c == '*' || *c == '/' || *c == '^') {
    return 1;
  }
  return 0;
}

int is_higher(char *c, char *top) {
  if (top == NULL || c == NULL) {
    return 0;
  }
  char temp1[255], temp2[255];
  strncpy(temp1, c, 1);
  strcpy(temp2, top);
  if (!strcmp(temp1, "^")) {
    if (!strcmp(temp2, "/") || !strcmp(temp2, "*") || !strcmp(temp2, "-") ||
        !strcmp(temp2, "+") || !strcmp(temp2, "mod")) {
      return 1;
    }
  }

  if (!strcmp(temp1, "/") || !strcmp(temp1, "*") || !strcmp(temp2, "mod")) {
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
    char value[255];
    dequeue(queue, value);
    strcpy(temp, value);
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

int isunary(char *index) {
  if (*index == '-' || *index == '+') {
    if (*(index - 1) == '(' || *(index - 1) == '-' || *(index - 1) == '+' ||
        *(index - 1) == '*' || *(index - 1) == '/') {
      return 1;
    }
  }
  return 0;
}

int operator_process(Stack *stack, Queue *queue, char *index) {
  if (isStackEmpty(stack) ||
      (!isStackEmpty(stack) && peek_compare(stack, "(")) ||
      is_higher(index, peek(stack))) {
    push(stack, index);

  } else {

    while (!isStackEmpty(stack) &&
           (!peek_compare(stack, "(") || is_lower(index, peek(stack)))) {

      enqueue(queue, pop(stack));
    }
    push(stack, index);
  }
  return 0;
}

int is_lower(char *c, char *top) {
  if (top == NULL || c == NULL) {
    return 0;
  }
  char temp1[255], temp2[255];
  strncpy(temp1, c, 1);
  strcpy(temp2, top);
  if (!strcmp(temp1, "+") || !strcmp(temp1, "-")) {
    if (!strcmp(temp2, "/") || !strcmp(temp2, "*") || !strcmp(temp2, "mod") ||
        !strcmp(temp2, "^")) {
      return 1;
    }
  }

  if (!strcmp(temp1, "/") || !strcmp(temp1, "*")) {
    if (!strcmp(temp2, "^")) {
      return 1;
    }
  }
  return 0;
}
int is_number(char *c) {
  char *next;

  strtod(c, &next);
  if (next == c || (*next != '\0')) {
    return 0;
  }
  return 1;
}

int calculation(Stack *stack, char *op, char *result) {
  char preresult[255];
  double first = strtod(pop(stack), NULL);
  double second = strtod(pop(stack), NULL);
  switch (*op) {
  case '+':
    snprintf(preresult, 255, "%lf", second + first);
    break;
  case '-':
    snprintf(preresult, 255, "%lf", second - first);
    break;
  case '*':
    snprintf(preresult, 255, "%lf", second * first);
    break;
  case '/':
    snprintf(preresult, 255, "%lf", second / first);
    break;
  case '^':
    snprintf(preresult, 255, "%lf", pow(second, first));
    break;
  default:
    break;
  }
  strcpy(result, preresult);
  return 0;
}