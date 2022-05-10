#include <iostream>
struct Node{
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
    int key;
    int value;
};

struct SimpleTree {
    Node *root = nullptr;
};

void insert(SimpleTree *tree, Node *n){
    Node *parent = nullptr;
    Node *view_node = tree->root;
    while (view_node != nullptr){
        parent = view_node;
        if (n->key < view_node->key){
            view_node = view_node->left;
        } else {
            view_node = view_node->right;
        }
    }
    n->parent = parent;
    if (parent == nullptr){
        tree->root = n;
    } else if (n->key < parent->key){
        parent->left = n;
    } else {
        parent->right = n;
    }
}

Node* search(Node *node, int key){
    while (node != nullptr && node->key != key){
        node = key < node->key ? node->left : node->right;
    }
    return node;
}

Node* minimum(Node *n){
    if (n == nullptr){
        return n;
    }
    while (n->left != nullptr){
        n = n->left;
    }
    return n;
}

Node* maximum(Node *n){
    if (n == nullptr){
        return n;
    }
    while (n->right != nullptr){
        n = n->right;
    }
    return n;
}

void remove(Node *root, int key){
    Node *m = minimum(root->right);
}

void clear(Node *root){
    if (root != nullptr) {
        clear(root->left);
        clear(root->right);
        delete root;
    }
}

void clear(SimpleTree *tree){
    clear(tree->root);
}

void print_nodes(Node *n){
    if (n != nullptr){
        std::cout << "  /" << n->parent->key << '/' << std::endl;
        std::cout << n->key << "\t— " << n->value << std::endl;
        print_nodes(n->left);
        print_nodes(n->right);
    }
}

void print_tree(SimpleTree tree){
    auto n = tree.root;
    std::cout << "SimpleTree:" << std::endl;
    std::cout << n->key << "\t— " << n->value << std::endl;
    print_nodes(n->left);

    print_nodes(n->right);
}

int main(){
    SimpleTree tree;
    for (int i = 0; i <= 10; ++i) {
        Node *n = new Node;
        n->key = i;
        n->value = 100*i-10*i*i;
        insert(&tree, n);
    }
    print_tree(tree);
    clear(&tree);
    return 0;
}
