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
        throw ;
    }
    auto pop_value = stack->head->value;
    auto new_head = stack->head->next;
    delete stack->head;
    stack->head = new_head;
    --stack->size;
    return pop_value;
}
// get the last element value
int top(Stack *stack) {
    return stack->head->value;
}
// true if stack is empty otherwise true
bool empty(Stack *stack) {
    return stack->size == 0;
}
// clear all elements of the stack
void clear(Stack *stack) {
    while (not empty(stack)){

    }
}/*
// print all elements of the stack
void print ( Stack * stack ) {
}
*/