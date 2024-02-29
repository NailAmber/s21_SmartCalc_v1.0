#include "calculus.h"

int infix_to_postfix(char *infix, char *postfix) {
  if (infix == NULL || postfix == NULL) {
    return 1;
  }
  char *index = infix;
  Queue queue;
  Stack stack;
  // createStack(&stack);
  // createQueue(&queue);

  while (*index != '\0') {
    printf("1\n");
    if (isdigit((unsigned char)*index)) {
      {
        printf("2\n");
        char data[255];
        snprintf(data, 255, "%f", strtod(index, &index));
        enqueue(&queue, data);
      }
    }

    if (isoperator(index)) {
      printf("3\n");
      printf("peak is %s\n", peek(&stack));
      printf("index is %s\n", index);
      if (isStackEmpty(&stack) ||
          (!isStackEmpty(&stack) && peek_compare(&stack, "(")) ||
          ishigher(index, peek(&stack))) {
        printf("34\n");
        printf("peak 34 is %s\n", peek(&stack));
        printf("index 34 is %s\n", index);
        push(&stack, index);
        printf("34\n");

      } else {

        while (!isStackEmpty(&stack) &&
               (peek_compare(&stack, "(") || !ishigher(index, peek(&stack)))) {

          enqueue(&queue, pop(&stack));
        }
        push(&stack, index);
      }
      index++;
    }
    if (*index == '(') {
      printf("4\n");
      push(&stack, "(");
      index++;
    }
    if (*index == ')') {
      printf("5\n");
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
int postfix_result(const char *postfix, long double *result);
