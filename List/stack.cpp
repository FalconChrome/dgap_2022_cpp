#include <iostream>
#include <cstdio>
#include <cstdint>

struct Node{
    int value;
    Node *next;
};

struct Stack{
    unsigned size = 0;
    Node *head = nullptr;
};

// adds new node with value new_val to the end
void push (Stack *stack, int new_val) {
    stack->head = new Node {new_val, stack->head};
    ++stack->size;
}

// get the last element value and delete last element
int pop(Stack *stack) {
    if (stack->head == nullptr){
        return INT32_MAX;
    }
    auto pop_value = stack->head->value;
    auto pop_head = stack->head;
    stack->head = stack->head->next;
    delete pop_head;
    --stack->size;
    return pop_value;
}
// get the last element value
int top(Stack *stack) {
    return stack->head->value;
}
// true if stack is empty otherwise true
bool empty(Stack *stack) {
    return stack->head == nullptr;
}
// clear all elements of the stack
void clear(Stack *stack) {
    Node *current = stack->head;
    Node *next;
    while (current != nullptr){
        next = current->next;
        delete current;
        current = next;
    }
    stack->head = nullptr;
    stack->size = 0;
}

// print all elements of the stack
void print(Stack *stack) {
    printf("%d-element Stack:\n[", stack->size);
    if (stack->size > 0) {
        printf("%d", stack->head->value);
        for (Node *n = stack->head->next; n != nullptr; n = n->next) {
            printf(", %d", n->value);
        }
    }
    printf("]\n");
}

int main(){
    Stack a;
    unsigned n = 7;
//    printf("Enter positive integer n: ");
//    scanf("%u", &n);
    printf("Filling a with 1..%d\n", n);
    for (int i = 1; i <= n; ++i) {
        push(&a, i);
    }
    print(&a);
    int x = pop(&a);
    printf("Popping:\na -> %d\n", x);
    x = top(&a);
    printf("Getting top:\na[0] = %d\n", x);
    push(&a, x);
    printf("Pushing:\n%d -> a\n", x);
    print(&a);
    printf("Clearing...\n");
    clear(&a);
    print(&a);
    return 0;
}