#include "calculus.h"

int infix_to_postfix(char *infix, char *postfix) {
  if (infix == NULL || postfix == NULL) {
    return 1;
  }
  char *index = infix;
  Queue queue;
  Stack stack;
  int first_loop = 1;
  while (*index != '\0') {
    if (first_loop || isunary(index)) {
      if (*index == '-') {
        enqueue(&queue, "-1.0");
        operator_process(&stack, &queue, "*");
        index++;
      }
      if (*index == '+') {
        index++;
      }
    }
    first_loop = 0;

    if (isdigit((unsigned char)*index)) {
      {
        char data[255];
        snprintf(data, 255, "%f", strtod(index, &index));
        enqueue(&queue, data);
      }
    }
    if (isalpha((unsigned char)*index)) {
      char data[255];
      snprintf(data, 2, "%s", index);
      enqueue(&queue, data);
      index++;
    }

    if (isoperator(index) && !isunary(index)) {
      operator_process(&stack, &queue, index);
      index++;
    }
    if (*index == '(') {
      push(&stack, "(");
      index++;
    }
    if (*index == ')') {
      while (!isStackEmpty(&stack) && !peek_compare(&stack, "(")) {
        enqueue(&queue, pop(&stack));
      }
      pop(&stack);
      index++;
    }
  }
  while (!isStackEmpty(&stack)) {
    enqueue(&queue, pop(&stack));
  }
  queue_to_string(&queue, postfix);
  removeQueue(&queue);
  removeStack(&stack);
  return 0;
}
int postfix_result(char *postfix, long double *result) {
  Stack stack;
  char *index = strtok(postfix, " ");

  while (index != NULL) {
    if (is_number(index)) {
      push(&stack, index);
    } else if (isoperator(index)) {
      char preresult[255];
      calculation(&stack, index, preresult);
      push(&stack, preresult);
    }
    index = strtok(NULL, " ");
  }
  *result = strtod(pop(&stack), NULL);
  removeStack(&stack);
  return 0;
}
