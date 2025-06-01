#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
    int data[MAX];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

int isFull(Queue *q) {
    return q->rear == MAX - 1;
}

void enqueue(Queue *q, int value) {
    if (isFull(q))
        return;
    if (isEmpty(q))
        q->front = 0;
    q->rear++;
    q->data[q->rear] = value;
}

int dequeue(Queue *q) {
    if (isEmpty(q))
        return -1;
    int value = q->data[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return value;
}

void display(Queue *q) {
    if (isEmpty(q))
        return;
    for (int i = q->front; i <= q->rear; i++)
        printf("%d ", q->data[i]);
    printf("\n");
}

int main() {
    Queue q;
    initQueue(&q);
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    display(&q);
    printf("Dequeued: %d\n", dequeue(&q));
    display(&q);
    return 0;
}
