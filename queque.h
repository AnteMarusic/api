
#ifndef API_QUEQUE_H
#define API_QUEQUE_H
struct ListNode {
    int value;
    struct ListNode *next;
};
struct Queue {
    struct ListNode *head;
    struct ListNode *tail;
    int dim;
};

struct Queue queue_create ();
void enqueue (struct Queue *this, int value);
int dequeue (struct Queue *this);
int isEmpty (struct Queue *this);
void queue_print (struct Queue *this);
#endif //API_QUEQUE_H
