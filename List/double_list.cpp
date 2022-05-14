//#include <iostream>
#include <cstdio>
#include <cstdint>

struct Node{
    Node *prev;
    Node *next;
    int value;
};

struct DoubleList {
    Node *head = nullptr;
    Node *tail = nullptr;
    unsigned size = 0;
};

// true if list is empty otherwise true
bool empty(DoubleList *list) {
    return list->size == 0;
}

// adds new node with value new_val to the end
void push_back(DoubleList *list, int new_val) {
    Node *new_node = new Node {list->tail, nullptr, new_val};
    if (empty(list)){
        list->head = new_node;
    } else {
        list->tail->next = new_node;
    }
    list->tail = new_node;
    ++list->size;
}
// add new node with value new_val to the front
void push_front(DoubleList *list, int new_val) {
    Node *new_node = new Node {nullptr, list->head, new_val};
    if (empty(list)){
        list->tail = new_node;
    } else {
        list->head->prev = new_node;
    }
    list->head = new_node;
    ++list->size;
}

// add new node with value new_val in front of i ‘ th node
void insert(DoubleList * list, unsigned idx, int new_val) {
    if (idx == 0){
        return push_front(list, new_val);
    }
    if (idx >= list->size){
        return push_back(list, new_val);
    }

    Node *next;
    if (2 * idx < list->size) {
        next = list->head;
        for (auto i = 0u; i < idx; ++i) {
            next = next->next;
        }
    } else {
        next = list->tail;
        for (auto i = list->size - 1; i > idx; --i) {
            next = next->prev;
        }
    }

    Node *new_node = new Node {next->prev, next, new_val};
    next->prev->next = new_node;
    next->prev = new_node;
    ++list->size;
}

// get the last element value and delete last element
int pop_back(DoubleList *list) {
    if (list->tail == nullptr){
        return INT32_MAX;
    }
    auto pop_value = list->tail->value;
    auto new_tail = list->tail->prev;
    delete list->tail;
    list->tail = new_tail;
    if (new_tail == nullptr) {
        list->head = new_tail;
    } else {
        new_tail->next = nullptr;
    }
    --list->size;
    return pop_value;
}
// get the front element value and delete front element
int pop_front(DoubleList *list) {
    if (list->head == nullptr){
        return INT32_MAX;
    }
    auto pop_value = list->head->value;
    auto new_head = list->head->next;
    delete list->head;
    list->head = new_head;
    if (new_head == nullptr){
        list->tail = new_head;
    } else {
        new_head->prev = nullptr;
    }
    --list->size;
    return pop_value;
}
// delete i ‘ th element
int remove(DoubleList *list, unsigned idx) {
    if (idx >= list->size){
        return INT32_MAX;
    }
    if (idx == list->size - 1){
        return pop_back(list);
    }
    if (idx == 0){
        return pop_front(list);
    }

    Node *rm_node;
    if (2 * idx < list->size) {
        rm_node = list->head;
        for (auto i = 0u; i < idx; ++i) {
            rm_node = rm_node->next;
        }
    } else {
        rm_node = list->tail;
        for (auto i = list->size-1; i > idx; --i) {
            rm_node = rm_node->prev;
        }
    }
    auto rm_value = rm_node->value;
    rm_node->prev->next = rm_node->next;
    rm_node->next->prev = rm_node->prev;
    delete rm_node;
    --list->size;
    return rm_value;
}

// get the length of the list
unsigned length(DoubleList *list) {
    return list->size;
}

// get the i ‘ th element by index
int get(DoubleList *list , unsigned idx) {
    if (idx >= list->size){
        return INT32_MAX;
    }
    Node *node;
    if (2 * idx < list->size) {
        node = list->head;
        for (auto i = 0u; i < idx; ++i) {
            node = node->next;
        }
    } else {
        node = list->tail;
        for (auto i = list->size - 1; i > idx; --i) {
            node = node->prev;
        }
    }
    return node->value;
}

// clear all elements of the list
void clear(DoubleList *list) {
    Node *current = list->head;
    Node *next;
    while (current != nullptr){
        next = current->next;
        delete current;
        current = next;
    }
    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
}

// print all elements of the list
void print(DoubleList *list) {
    printf("%d-element DoubleList:\n[", list->size);
    for (Node *n = list->head; n != list->tail; n = n->next) {
        printf("%d, ", n->value);
    }
    if (list->size > 0) {
        printf("%d", list->tail->value);
    }
    printf("]\n");
}
// print all elements of the list in reverse
void printReverse(DoubleList *list) {
    printf("%d-element DoubleList (reversed):\n[", list->size);
    for (Node *n = list->tail; n != list->head; n = n->prev) {
        printf("%d, ", n->value);
    }
    if (list->size > 0) {
        printf("%d", list->head->value);
    }
    printf("]\n");
}

int main(){
    DoubleList a;
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
    printf("Inserting:\n%d -> a[%d]\n", x, length(&a) / 4);
    x = remove(&a, length(&a) / 3);
    printf("Removing:\na[%d] = %d\n", length(&a) / 3, x);
    print(&a);
    x = get(&a, length(&a) / 2);
    printf("Getting:\na[%d] = %d\n", length(&a) / 2, x);
    push_front(&a, x);
    printf("Pushing front:\n%d -> a[0]\n", x);
    printReverse(&a);
    printf("Clearing...\n");
    clear(&a);
    print(&a);
    return 0;
}