#include "calculus.h"

Stack *createStack() {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->top = NULL;
  return stack;
}

int isStackEmpty(const Stack *stack) { return (stack->top == NULL); }

void push(Stack *stack, char *data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = (char *)malloc(strlen(data) + 1);
  char temp[255];
  if (!is_number(data) && isoperator(data)) {

    snprintf(temp, 2, "%s", data);
    strcpy(newNode->data, temp);
  } else {
    strcpy(temp, data);
    strcpy(newNode->data, temp);
  }
  newNode->next = stack->top;
  stack->top = newNode;
}
char *pop(Stack *stack) { // МЕНЯЕМ ВСЕ ТУТ ОШИБКА ДОЛЖНА БЫТЬ!!!!!!!!!!
  if (isStackEmpty(stack)) {
    return NULL;
  }
  char *data = stack->top->data;
  Node *temp = stack->top;
  stack->top = stack->top->next;
  printf("freee\n");
  free(temp->data);
  free(temp);
  return data;
}

char *peek(const Stack *stack) {
  if (stack == NULL || isStackEmpty(stack)) {
    return "error";
  }
  return stack->top->data;
}
void removeStack(Stack *stack) {
  while (!isStackEmpty(stack)) {
    pop(stack);
  }
}

Queue *createQueue() {
  Queue *queue = (Queue *)malloc(sizeof(Queue));
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
}

int isQueueEmpty(const Queue *queue) { return (queue->front == NULL); }

void enqueue(Queue *queue, char *data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = (char *)malloc(strlen(data) + 1);
  char temp[255];
  strcpy(temp, data);
  strcpy(newNode->data, temp);
  newNode->next = NULL;
  if (isQueueEmpty(queue)) {
    queue->front = newNode;
    queue->rear = newNode;
  } else {
    queue->rear->next = newNode;
    queue->rear = newNode;
  }
}
int dequeue(Queue *queue, char *string) {
  if (isQueueEmpty(queue)) {
    return 1;
  }
  char *data;
  data = (char *)malloc(strlen(queue->front->data) + 1);
  strcpy(data, queue->front->data);
  Node *temp = queue->front;
  queue->front = queue->front->next;
  if (queue->front == NULL) {
    queue->rear = NULL;
  }
  printf("freee\n");
  strcpy(string, data);
  free(temp->data);
  free(temp);
  free(data);
  return 0;
}
char *front(Queue *queue) {
  if (isQueueEmpty(queue)) {
    return NULL;
  }
  return queue->front->data;
}
void removeQueue(Queue *queue) {
  while (!isQueueEmpty(queue)) {
    dequeue(queue, NULL);
  }
}