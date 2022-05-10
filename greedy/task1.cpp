#include "qsort.h"
#include <iostream>

void task1(){
    int S, N;
    std::cin >> S >> N;
    int users[100];
    for (int i = 0; i < N; ++i) {
        std::cin >> users[i];
    }

    qsort(users, N);
    int m = 0;
    int i;
    for (i = 0; i < N; ++i) {
        m += users[i];
        if(m > S){
            break;
        }
    }
    std::cout << i;
}
