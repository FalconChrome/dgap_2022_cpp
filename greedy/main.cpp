#include "main.h"
#include <cstdio>
#define TASK0 task2
using namespace std;

int main() {
    char task = '2';
    scanf("%c", &task);
    switch (task) {
        case '\n':
            TASK0();
            break;
        case '1':
            task1();
            break;
        case '2':
            task2();
            break;
//        case 3:
//            task3();
//            break;
        default:
            break;
    }
    return 0;
}
