#include "calculus.h"

int infix_to_postfix(char *infix, char *postfix) {
  if (infix == NULL || postfix == NULL) {
    return 1;
  }
  char *index = infix;
  Queue *queue;
  Stack *stack;
  createQueue(&queue);
  createStack(&stack);
  int first_loop = 1;
  while (*index != '\0') {
    while (*index == ' ')
    {
      index++;
    }
    
    number_process(stack, queue, &index, &first_loop);
    if (isoperator(index) && !isunary(index)) {
      operator_process(stack, queue, index);
      index++;
    }
    if (*index == '(') {
      push(stack, "(");
      index++;
    }
    if (*index == ')') {
      while (!isStackEmpty(stack) && !peek_compare(stack, "(")) {
        char temp[255] = {'\0'};
        pop(stack, temp);
        enqueue(queue, temp);
      }
      pop(stack, NULL);
      index++;
    }
  }
  while (!isStackEmpty(stack)) {
    char temp[255] = {'\0'};
    pop(stack, temp);
    enqueue(queue, temp);
  }
  queue_to_string(queue, postfix);
  removeQueue(queue);
  removeStack(stack);
  return 0;
}

int postfix_result(char *postfix, long double *result) {
  Stack *stack;
  createStack(&stack);
  char *index = strtok(postfix, " ");
  int first_loop = 1;
  while (index != NULL) {
    if (first_loop && is_number(index)) {
      printf("main peek is %s\n", peek(stack));
      push(stack, index);
      printf("main index is %s\n", index);
    } else if (is_number(index)) {
      printf("main peek is %s\n", peek(stack));
      push(stack, index);
      printf("main index is %s\n", index);
    } else if (isoperator(index)) {
      char preresult[255];
      int error = calculation(stack, index, preresult);
      if (error == 2)
      {
        printf("ERROR ZERO /\n");
        removeStack(stack);
        return 2;
      } else 
      if (error == 1) {
        printf("ERROR\n");
        removeStack(stack);
        return 1;
      }

      push(stack, preresult);
    }
    index = strtok(NULL, " ");
    first_loop = 0;
  }
  char temp[255] = {'\0'};
  pop(stack, temp);
  *result = strtod(temp, NULL);
  removeStack(stack);
  return 0;
}
