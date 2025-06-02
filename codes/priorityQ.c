#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char email[256];
    int priority;
} Email;

typedef struct {
    Email *heap;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* createQueue(int capacity) {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    pq->heap = malloc(sizeof(Email) * capacity);
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void swap(Email *a, Email *b) {
    Email temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleUp(PriorityQueue *pq, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (pq->heap[index].priority <= pq->heap[parent].priority)
            break;
        swap(&pq->heap[index], &pq->heap[parent]);
        index = parent;
    }
}

void bubbleDown(PriorityQueue *pq, int index) {
    int left, right, maxIndex;
    while (1) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        maxIndex = index;

        if (left < pq->size && pq->heap[left].priority > pq->heap[maxIndex].priority)
            maxIndex = left;
        if (right < pq->size && pq->heap[right].priority > pq->heap[maxIndex].priority)
            maxIndex = right;
        if (maxIndex == index)
            break;
        swap(&pq->heap[index], &pq->heap[maxIndex]);
        index = maxIndex;
    }
}

void enqueue(PriorityQueue *pq, char *email, int priority) {
    if (pq->size == pq->capacity) {
        pq->capacity *= 2;
        pq->heap = realloc(pq->heap, sizeof(Email) * pq->capacity);
    }
    strcpy(pq->heap[pq->size].email, email);
    pq->heap[pq->size].priority = priority;
    bubbleUp(pq, pq->size);
    pq->size++;
}

Email dequeue(PriorityQueue *pq) {
    Email maxEmail = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;
    bubbleDown(pq, 0);
    return maxEmail;
}

int isEmpty(PriorityQueue *pq) {
    return pq->size == 0;
}

int main() {
    PriorityQueue *pq = createQueue(10);

    enqueue(pq, "marketing_campaign@example.com", 10);
    enqueue(pq, "security_alert@example.com", 100);
    enqueue(pq, "order_confirmation@example.com", 70);
    enqueue(pq, "password_reset@example.com", 105);
    enqueue(pq, "newsletter@example.com", 30);

    while (!isEmpty(pq)) {
        Email e = dequeue(pq);
        printf("Sending email: %s with priority %d\n", e.email, e.priority);
    }

    free(pq->heap);
    free(pq);
    return 0;
}
