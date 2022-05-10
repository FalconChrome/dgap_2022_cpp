#include <iostream>

struct Node{
    int value;
    Node *next;
};
int main() {
    int x = INT32_MIN;
    std::cout << x;
    Node *n = new Node {3, nullptr};
    delete n;
    std::cout << (n == nullptr);
    return 0;
}
