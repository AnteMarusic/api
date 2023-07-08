#include "queque.h"
#include <stdlib.h>
#include <stdio.h>

struct Queue queue_create () {
    struct Queue queue;
    queue.head = NULL;
    queue.tail = NULL;
    queue.dim = 0;
    return queue;
}

void enqueue (struct Queue *this, int value) {
    struct ListNode *newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->value = value;
    newNode->next = NULL;
    if (this->head == NULL) {
        this->head = newNode;
        this->tail = newNode;
    } else {
        this->tail->next = newNode;
        this->tail = newNode;
    }
    this->dim++;
}

int dequeue (struct Queue *this) {
    if (this->head == NULL) {
        return -1;
    }
    struct ListNode *toRemove = this->head;
    int value = toRemove->value;
    this->head = this->head->next;
    free(toRemove);
    this->dim--;
    return value;
}

int isEmpty (struct Queue *this) {
    return this->dim == 0;
}

void queue_print (struct Queue *this) {
    int i;
    struct ListNode *temp;
    if (this->dim == 0) {
        printf("la coda è vuota \n");
    }
    else {
        printf("head : ");
        temp = this->head;
        for (i = 0; i < this->dim; i ++) {
            printf("%d ", temp->value);
            if (this->dim - i - 1 == 0) {
                break;
            }
            temp = temp->next;
        }
        printf("\n");
    }
}
