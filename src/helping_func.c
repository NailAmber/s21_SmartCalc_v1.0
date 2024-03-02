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
  char temp1[255] = {'\0'}, temp2[255] = {'\0'};
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
    char temp[255] = {'\0'};
    char value[255] = {'\0'};
    // printf("to string, front is %s\n", front(queue));
    dequeue(queue, value);
    // printf("value is %s\n", value);
    strcpy(temp, value);
    // printf("temp is %s\n", temp);
    strcat(string, temp);
    if (!isQueueEmpty(queue)) {
      strcat(string, " ");
    }
  }
  return 0;
}

int peek_compare(Stack *stack, char *string) {
  if (stack == NULL || string == NULL || isStackEmpty(stack)) {
    return 0;
  }
  char temp[255] = {'\0'};
  strcpy(temp, peek(stack));
  return !strcmp(temp, string);
}

int isunary(char *index) {
  if (*index == '-' || *index == '+') {
    if (*(index - 1) == '(' || *(index - 1) == '-' || *(index - 1) == '+' ||
        *(index - 1) == '*' || *(index - 1) == '/' || *(index - 1) == '^') {
      return 1;
    }
  }
  return 0;
}

int operator_process(Stack *stack, Queue *queue, char *index) {
  // printf("peek is %s\n", peek(stack));
  // printf("front is %s\n", front(queue));
  if (isStackEmpty(stack) ||
      (!isStackEmpty(stack) && peek_compare(stack, "(")) ||
      is_higher(index, peek(stack))) {
    // printf("pushing... %s\n", index);
    char temp[255];
    snprintf(temp, 2, "%s", index);
    push(stack, temp);

  } else {
    // printf("operator\n");
    while (!isStackEmpty(stack) &&
           (!peek_compare(stack, "(") || is_lower(index, peek(stack)))) {

      char temp[255] = {'\0'};
      pop(stack, temp);
      enqueue(queue, temp);
    }
    char temp[255] = {'\0'};
    snprintf(temp, 2, "%s", index);
    push(stack, temp);
  }
  return 0;
}

int number_process(Stack *stack, Queue *queue, char **index, int *first_loop) {
  if (*first_loop || isunary(*index)) {
    if (**index == '-') {
      if (*(*index+1) == '(' || *(*index+1) == '-' || *(*index+1) == '+' || *(*index+1) == ' ')
      {
        enqueue(queue, "-1");
        push(stack, "*");
        *index += 1;
      } else{
      
      char data[255] = {'\0'};
      snprintf(data, 255, "%.8lf", strtod(*index, index));
      enqueue(queue, data);
      printf("just = %s\n", peek(stack));
      printf("index is %s\n", *index);
      }
    }
    if (**index == '+') {
      *index += 1;
    }
  }
  *first_loop = 0;
  if (isdigit((unsigned char)**index)) {
    {
      char data[255] = {'\0'};
      snprintf(data, 255, "%.8f", strtod(*index, index));
      enqueue(queue, data);
    }
  }
  if (isalpha((unsigned char)**index)) {
    char data[255] = {'\0'};
    snprintf(data, 2, "%s", *index);
    enqueue(queue, data);
    *index += 1;
  }
  return 0;
}

int is_lower(char *c, char *top) {
  if (top == NULL || c == NULL) {
    return 0;
  }
  char temp1[255] = {'\0'}, temp2[255] = {'\0'};
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
  char preresult[255] = {'\0'};
  char temp[255] = {'\0'};
   printf("peak 1 is %s\n", peek(stack));
  if (!strcmp(peek(stack), "error"))
  {
    return 1;
  }
  pop(stack, temp);
   printf("peak 2 is %s\n", peek(stack));
  if (!strcmp(peek(stack), "error"))
  {
    return 1;
  }
  
  double first = strtod(temp, NULL);
  printf("calc peak is %s\n", peek(stack));
  pop(stack, temp);
  double second = strtod(temp, NULL);
  printf("calc first is %lf\n", first);
  printf("calc second is %lf\n", second);
  printf("calc operator is %s\n", op);

  if (fabs(first) < 1e-7) {
    return 2;
  }

  switch (*op) {
  case '+':
    snprintf(preresult, 255, "%.8lf", second + first);
    break;
  case '-':
    snprintf(preresult, 255, "%.8lf", second - first);
    break;
  case '*':
    snprintf(preresult, 255, "%.8lf", second * first);
    break;
  case '/':
    snprintf(preresult, 255, "%.8lf", second / first);
    break;
  case '^':
    snprintf(preresult, 255, "%.8lf", pow(second, first));
    break;
  default:
    break;
  }
  strcpy(result, preresult);
  return 0;
}