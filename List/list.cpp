//#include <iostream>
#include <cstdio>
#include <cstdint>

struct Node{
    int value;
    Node *next;
};

struct List {
    unsigned size = 0;
    Node *head = nullptr;
    Node *tail = nullptr;
};

// true if list is empty otherwise true
bool empty(List *list) {
    return list->size == 0;
}

// adds new node with value new_val to the end
void push_back(List *list, int new_val) {
    Node *new_node = new Node {new_val, nullptr};
    if (empty(list)){
       list->head = new_node;
    } else {
       list->tail->next = new_node;
    }
    list->tail = new_node;
    ++list->size;
}
// add new node with value new_val to the front
void push_front(List *list, int new_val) {
    list->head = new Node {new_val, list->head};
    if (list->tail == nullptr){
        list->tail = list->head;
    }
    ++list->size;
}

// add new node with value new_val in front of i ‘ th node
void insert(List * list, unsigned idx, int new_val) {
    if (idx == 0){
        return push_front(list, new_val);
    }
    if (idx >= list->size){
        return push_back(list, new_val);
    }

    Node *prev = list->head;
    for (int i = 0; i < idx - 1; ++i) {
        prev = prev->next;
    }
    prev->next = new Node {new_val, prev->next};
    ++list->size;
}
// get the last element value and delete last element
int pop_back(List *list) {
    if (list->tail == nullptr){
        return INT32_MAX;
    }
    auto pop_value = list->tail->value;
    Node *new_tail = nullptr;
    if (list->head != list->tail) {
        for (new_tail = list->head; new_tail->next != list->tail; new_tail = new_tail->next) {}
        new_tail->next = nullptr;
    } else {
        list->head = new_tail;
    }
    delete list->tail;
    list->tail = new_tail;
    --list->size;
    return pop_value;
}
// get the front element value and delete front element
int pop_front(List *list) {
    if (list->head == nullptr){
        return INT32_MAX;
    }
    auto pop_value = list->head->value;
    auto new_head = list->head->next;
    delete list->head;
    list->head = new_head;
    if (new_head == nullptr){
        list->tail = new_head;
    }
    --list->size;
    return pop_value;
}
// delete i ‘ th element
int remove(List *list, unsigned idx) {
    if (idx >= list->size){
        return INT32_MAX;
    }
    if (idx == list->size - 1){
        return pop_back(list);
    }
    if (idx == 0){
        return pop_front(list);
    }

    Node *prev = list->head;
    for (int i = 0; i < idx - 1; ++i) {
        prev = prev->next;
    }
    auto removed_value = prev->next->value;
    auto removed_node = prev->next;
    prev->next = removed_node->next;
    delete removed_node;
    --list->size;
    return removed_value;
}

// get the length of the list
unsigned length(List *list) {
    return list->size;
}

// get the i ‘ th element by index
int get(List *list , unsigned idx) {
    if (idx >= list->size){
        return INT32_MAX;
    }
    Node *n = list->head;
    for (int i = 0; i < idx; ++i) {
        n = n->next;
    }
    return n->value;
}

// clear all elements of the list
void clear(List *list) {
   Node *current = list->head;
   Node *next;
   list->head = nullptr;
   list->tail = nullptr;
   while (current != list->tail){
       next = current->next;
       delete current;
       current = next;
   }
   list->size = 0;
}

// print all elements of the list
void print(List *list) {
    printf("%d-element List:\n[", list->size);
    for (Node *n = list->head; n != list->tail; n = n->next) {
        printf("%d, ", n->value);
    }
    if (list->size > 0) {
        printf("%d", list->tail->value);
    }
    printf("]\n");
}

int main(){
    List a;
    unsigned n = 12;
//    printf("Enter positive integer n: ");
//    scanf("%u", &n);
    printf("Filling a with 0..%d\n", n-1);
    for (int i = 0; i < n; ++i) {
        push_back(&a, i);
    }
    print(&a);
    int x = pop_front(&a);
    printf("Popping front:\na[0] = %d\n", x);
    x = pop_back(&a);
    printf("Popping back:\na[%d] = %d\n", length(&a), x);
    print(&a);
    insert(&a, length(&a) / 4, x);
    printf("Inserting:\na[%d] = %d\n", length(&a) / 4, x);
    x = remove(&a, length(&a) / 3);
    printf("Removing:\na[%d] = %d\n", length(&a) / 3, x);
    print(&a);
    x = get(&a, length(&a) / 2);
    printf("Getting:\na[%d] = %d\n", length(&a) / 2, x);
    push_front(&a, x);
    printf("Pushing front:\n%d -> a[0]\n", x);
    print(&a);
    printf("Clearing...\n");
    clear(&a);
    print(&a);
    return 0;
}