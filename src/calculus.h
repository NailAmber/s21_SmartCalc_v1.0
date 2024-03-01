#ifndef CALKULUS_H_
#define CALKULUS_H_

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char *data;
  struct Node *next;
} Node;

typedef struct Stack {
  Node *top;
} Stack;

typedef struct Queue {
  Node *front;
  Node *rear;
} Queue;

Stack *createStack();
int isStackEmpty(const Stack *stack);
void push(Stack *stack, char *data);
char *pop(Stack *stack);
char *peek(const Stack *stack);
void removeStack(Stack *stack);

Queue *createQueue();
int isQueueEmpty(const Queue *queue);
void enqueue(Queue *queue, char *data);
int dequeue(Queue *queue, char *string);
char *front(Queue *queue);
void removeQueue(Queue *queue);

int infix_to_postfix(char *infix, char *postfix);
int postfix_result(char *postfix, long double *result);

int isoperator(char *c);
int is_higher(char *c, char *top);
int is_lower(char *c, char *top);
int queue_to_string(Queue *queue, char *string);
int peek_compare(Stack *stack, char *string);
int isunary(char *index);
int operator_process(Stack *stack, Queue *queue, char *index);
int is_number(char *c);
int calculation(Stack *stack, char *op, char *result);

#endif // CALKULUS_H_
