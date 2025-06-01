#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char task[100];
    int priority;
} Task;

typedef struct {
    Task data[MAX];
    int top;
} Stack;

typedef struct {
    Task data[MAX];
    int size;
} PriorityQueue;

void initStack(Stack* s) {
    s->top = -1;
}

int isStackEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, Task t) {
    if (s->top < MAX - 1) {
        s->data[++s->top] = t;
    }
}

Task pop(Stack* s) {
    return s->data[s->top--];
}

void initPriorityQueue(PriorityQueue* pq) {
    pq->size = 0;
}

void swap(Task* a, Task* b) {
    Task temp = *a;
    *a = *b;
    *b = temp;
}

void insertPriorityQueue(PriorityQueue* pq, Task t) {
    if (pq->size < MAX) {
        pq->data[pq->size] = t;
        int i = pq->size;
        while (i > 0 && pq->data[(i - 1) / 2].priority < pq->data[i].priority) {
            swap(&pq->data[i], &pq->data[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
        pq->size++;
    }
}

Task removePriorityQueue(PriorityQueue* pq) {
    Task topTask = pq->data[0];
    pq->data[0] = pq->data[--pq->size];
    int i = 0;
    while (1) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < pq->size && pq->data[left].priority > pq->data[largest].priority)
            largest = left;
        if (right < pq->size && pq->data[right].priority > pq->data[largest].priority)
            largest = right;
        if (largest != i) {
            swap(&pq->data[i], &pq->data[largest]);
            i = largest;
        } else {
            break;
        }
    }
    return topTask;
}

int main() {
    Stack stack;
    PriorityQueue pq;
    initStack(&stack);
    initPriorityQueue(&pq);

    Task t1 = {"Task1", 1};
    Task t2 = {"Task2", 5};
    Task t3 = {"Task3", 3};
    Task t4 = {"Task4", 4};

    push(&stack, t1);
    push(&stack, t2);
    push(&stack, t3);

    while (!isStackEmpty(&stack)) {
        Task t = pop(&stack);
        insertPriorityQueue(&pq, t);
    }

    insertPriorityQueue(&pq, t4);

    printf("Processing tasks by priority:\n");
    while (pq.size > 0) {
        Task t = removePriorityQueue(&pq);
        printf("Task: %s, Priority: %d\n", t.task, t.priority);
    }

    return 0;
}
