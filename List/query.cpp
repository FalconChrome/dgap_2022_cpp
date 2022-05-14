#include <iostream>
#include <cstdio>
#include <cstdint>

struct Node{
    int value;
    Node *next;
};

struct Queue{
    unsigned size = 0;
    Node *head = nullptr;
    Node *tail = nullptr;
};

// adds new node with value new_val to the end
void enQueue(Queue *queue, int new_val) {
    auto new_node  = new Node {new_val, nullptr};
    if (queue->tail == nullptr){
        queue->head = new_node;
    } else {
        queue->tail->next = new_node;
    }
    queue->tail = new_node;
    ++queue->size;
}

// get the front element value and delete last element
int deQueue(Queue *queue) {
    if (queue->head == nullptr){
        return INT32_MAX;
    }
    auto pop_value = queue->head->value;
    auto pop_head = queue->head;
    queue->head = queue->head->next;
    if (queue->head == nullptr){
        queue->tail = queue->head;
    }
    delete pop_head;
    --queue->size;
    return pop_value;
}

// get the front element value
int front(Queue *queue) {
    return queue->head->value;
}
// get the last element value
int rear(Queue *queue) {
    return queue->tail->value;
}

// get the length of the queue
unsigned length(Queue *queue){
    return queue->size;
}
// true if queue is empty otherwise true
bool empty(Queue *queue) {
    return queue->size == 0;
}

// clear all elements of the queue
void clear(Queue *queue) {
    Node *current = queue->head;
    Node *next;
    while (current != nullptr){
        next = current->next;
        delete current;
        current = next;
    }
    queue->head = nullptr;
    queue->tail = nullptr;
    queue->size = 0;
}

// print all elements of the queue
void print(Queue *queue) {
    printf("%d-element Queue:\n[", queue->size);
    if (queue->size > 0) {
        printf("%d", queue->head->value);
        for (Node *n = queue->head->next; n != nullptr; n = n->next) {
            printf(", %d", n->value);
        }
    }
    printf("]\n");
}

int main(){
    Queue a;
    unsigned n = 9;
//    printf("Enter positive integer n: ");
//    scanf("%u", &n);
    printf("Filling a with 1..%d\n", n);
    for (int i = 1; i <= n; ++i) {
        enQueue(&a, i);
    }
    print(&a);
    int x = deQueue(&a);
    printf("Dequeuing:\na -> %d\n", x);
    x = rear(&a);
    printf("Getting rear:\na[%d] = %d\n", length(&a) - 1, x);
    x = front(&a);
    printf("Getting front:\na[0] = %d\n", x);
    enQueue(&a, x);
    printf("Enqueuing:\n%d -> a\n", x);
    print(&a);
    printf("Clearing...\n");
    clear(&a);
    print(&a);
    return 0;
}
