#include <iostream>

int trib(int n){
    if (n < 3){
        return (int)(n > 0);
    }
    int query[3] = {0, 1, 1};
    int tail = 2;
    for (int i = 3; i <= n; ++i) {
        tail = (tail + 1) % 3;
        query[tail] = query[0] + query[1] + query[2];
    }
    return query[tail];
}

int main(){
    int n;
    std::cin >> n;
    std::cout << trib(n) << '\n';
    return 0;
}
