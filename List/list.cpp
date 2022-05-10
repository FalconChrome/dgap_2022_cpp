struct Node{
    int value;
    Node *next;
};

struct List {
    unsigned size ;
    Node * head ;
    Node * tail ;
};

// adds new node with value new_val to the end
void push_back ( List * list , int new_val ) {
// code here
}
// add new node with value new_val to the front
void push_front ( List * list , int new_val ) {
// code here
}
// add new node with value new_val in front of i ‘ th node
void insert ( List * list , unsigned idx , int new_val ) {
// code here
}
// get the last element value and delete last element
int pop_back ( List * list ) {
// code here
}
// get the front element value and delete last element
int pop_front ( List * list ) {
// code here
}
// delete i ‘ th element
int remove ( List * list , unsigned idx ) {
// code here
}
// get the length of the list
unsigned length ( List * list ) {
// code here
}
// get the i ‘ th element by index
int get ( List * list , unsigned idx ) {
// code here
}
// clear all elements of the list
void clear ( List * list ) {
// code here
}
// print all elements of the list
void print ( List * list ) {
