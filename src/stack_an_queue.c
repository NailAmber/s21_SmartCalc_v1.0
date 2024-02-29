#include "calculus.h"

Stack *createStack() {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->top = NULL;
  return stack;
}

int isStackEmpty(const Stack *stack) { return (stack->top == NULL); }

void push(Stack *stack, char *data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (isoperator(data)) {
    char temp[255];
    snprintf(temp, 2, "%s", data);
    newNode->data = temp;
  } else {
    newNode->data = data;
  }
  newNode->next = stack->top;
  stack->top = newNode;
}
char *pop(Stack *stack) {
  if (isStackEmpty(stack)) {
    return NULL;
  }
  char *data = stack->top->data;
  Node *temp = stack->top;
  stack->top = stack->top->next;
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
  char temp[255];
  strcpy(temp, data);
  newNode->data = temp;
  newNode->next = NULL;
  if (isQueueEmpty(queue)) {
    queue->front = newNode;
    queue->rear = newNode;
  } else {
    queue->rear->next = newNode;
    queue->rear = newNode;
  }
}
char *dequeue(Queue *queue) {
  if (isQueueEmpty(queue)) {
    return NULL;
  }
  char *data = queue->front->data;
  Node *temp = queue->front;
  queue->front = queue->front->next;
  if (queue->front == NULL) {
    queue->rear = NULL;
  }
  free(temp);
  return data;
}
char *front(Queue *queue) {
  if (isQueueEmpty(queue)) {
    return NULL;
  }
  return queue->front->data;
}
void removeQueue(Queue *queue) {
  while (!isQueueEmpty(queue)) {
    dequeue(queue);
  }
}