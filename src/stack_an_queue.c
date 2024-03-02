#include "calculus.h"

int createStack(Stack **stack) {
  *stack = (Stack *)malloc(sizeof(Stack));
  (*stack)->top = NULL;
  return 0;
}

int isStackEmpty(const Stack *stack) { return (stack->top == NULL); }

void push(Stack *stack, char *data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = (char *)malloc(strlen(data) + 1);
  char temp[255] = {"\0"};
  strcpy(temp, data);
  strcpy(newNode->data, temp);
  newNode->next = stack->top;
  stack->top = newNode;
}
int pop(Stack *stack, char *string) {
  if (isStackEmpty(stack)) {
    return 1;
  }
  char *data;
  data = (char *)malloc(strlen(stack->top->data) + 1);
  strcpy(data, stack->top->data);
  Node *temp = stack->top;
  stack->top = stack->top->next;
  // printf("freee1\n");
  if (string != NULL) {
    strcpy(string, data);
  }

  free(temp->data);
  free(temp);
  free(data);
  return 0;
}

char *peek(const Stack *stack) {
  if (stack == NULL || isStackEmpty(stack)) {
    return "error";
  }
  return stack->top->data;
}
void removeStack(Stack *stack) {
  while (!isStackEmpty(stack)) {
    pop(stack, NULL);
  }
  free(stack);
}

int createQueue(Queue **queue) {
  *queue = (Queue *)malloc(sizeof(Queue));
  (*queue)->front = NULL;
  (*queue)->rear = NULL;
  // printf("queue front %d\n", (*queue)->front == NULL);
  return 0;
}

int isQueueEmpty(const Queue *queue) { return (queue->front == NULL); }

void enqueue(Queue *queue, char *data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = (char *)malloc(strlen(data) + 1);
  char temp[255] = {'\0'};
  strcpy(temp, data);
  // printf("temp enqueue is %s\n", temp);
  strcpy(newNode->data, temp);

  newNode->next = NULL;
  // printf("queue front %d\n", queue->front == NULL);
  if (isQueueEmpty(queue)) {
    queue->front = newNode;
    queue->rear = newNode;
    // printf("newnode data enqueue 1 is %s\n", newNode->data);
  } else {
    queue->rear->next = newNode;
    queue->rear = newNode;
    // printf("newnode data enqueue 2 is %s\n", newNode->data);
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
  // printf("freee\n");
  strcpy(string, data);
  free(temp->data);
  free(temp);
  free(data);
  return 0;
}
char *front(Queue *queue) {
  if (queue == NULL || isQueueEmpty(queue)) {
    return "error";
  }
  // printf("front data is %s\n", queue->front->data);
  return queue->front->data;
}
void removeQueue(Queue *queue) {
  while (!isQueueEmpty(queue)) {
    dequeue(queue, NULL);
  }
  free(queue);
}