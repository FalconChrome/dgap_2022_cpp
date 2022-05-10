#include <iostream>

void task2(){
    int N, k, S;
    int station[1000];
    std::cin >> N >> k;
    std::cin >> S;
    for (int i = 0; i < S; ++i) {
        std::cin >> station[i];
    }
//    qsort(station, N);
    int n = 0;
    int last = 0;
    for (int i = 0; i < S; ++i) {
        if ((station[i] - last) > k){
            if (station[--i] == last){
                n = -1;
                break;
            }
            last = station[i];
            ++n;
            continue;
        }
    }
    if ((N - last) > k){
        if ((N - station[S - 1]) > k){
            n = -1;
        } else {
            ++n;
        }
    }
    std::cout << n;
}
