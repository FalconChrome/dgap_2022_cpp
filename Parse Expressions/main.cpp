#include <iostream>

bool check_brackets(const char *s, int size){
    static char brackets[] = "()[]{}<>";
    char *open_bracket_stack = new char[size / 2];
    unsigned int depth = 0;
    char t;
    bool result = true;
    for (int i = 0; i < size; ++i) {
        t = s[i];
        for (int j = 0; j < 4; ++j) {
            if (t == brackets[2*j]){
                if (depth == size / 2){
                    result = false;
                    break;
                }
                open_bracket_stack[depth++] = t;
                break;
            }
            if (t == brackets[2*j+1]){
                if (depth == 0){
                    result = false;
                    break;
                }
                if (brackets[2*j] != open_bracket_stack[--depth]){
                    result = false;
                    break;
                }
                break;
            }
        }
        if (not result){
            break;
        }
    }
    delete []open_bracket_stack;
    return result;
}

int eval_expr(char *expr, int size);

struct Node{
    int value;
    Node *next;
};


int main() {
//    std::cout << '('+0 << ')'+0 << '['+0 << ']'+0 << '{'+0 << '}'+0 << '<'+0 << '>'+0 << std::endl;
    /*int n;
    std::cin >> n;
    char *s = new char[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> s[i];
    }
    bool corr = check_brackets(s, n);
    std::cout << (corr ? "true" : "false") << std::endl;
    auto *s = new Stack();
    push(s, 5);
    std::cout << s->head << " " << s->head->value << s->size;
    delete s->head;
    delete s;*/
    auto *n = new Node{0, nullptr};
    std::cout << n->value << ' ' << n->next << ' ' << n->next->value;
    return 0;
}
