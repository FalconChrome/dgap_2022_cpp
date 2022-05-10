#include <iostream>

struct Rod {
    int len;
    int price;
};

int cut_rod_recursive(Rod *p, int n) {
    if (n == 0) {
        return 0;
    }
    int q = -1;
    for (auto i = 1; p[i - 1].len <= 10 && i <= n; ++i) {
        q = std::max(q, p[i - 1].price + cut_rod_recursive(p, n - i));
    }
    return q;
}

int cut_rod_helper(Rod *p, int n, int *memo) {
    if (memo[n] >= 0) {
        return memo[n];
    }
    if (n == 0) {
        memo[n] = 0;
        return memo[n];
    }
    int q = -1;
    for (auto i = 1; p[i - 1].len <= 10 && i <= n; ++i) {
        q = std::max(q, p[i - 1].price + cut_rod_helper(p, n - i, memo));
    }
    memo[n] = q;
    return q;
}

int cut_rod_memoization(Rod *p, int n) {
    int *array = new int[n + 1];
    for (auto i = 0; i <= n; ++i) {
        array[i] = -1;
    }
    int result = cut_rod_helper(p, n, array);
    delete []array;
    return result;
}

int cut_rod_asc(Rod *p, int n){
    int *max_price = new int[n + 1]{0};
    int q;
    for (int i = 1; i <= n; ++i) {
        q = 0;
        for (int j = 1; (j <= 10) && (j <= i); ++j) {
            if (q < max_price[i - j] + p[j - 1].price){
                q = max_price[i - j] + p[j - 1].price;
            }
        }
        max_price[i] = q;
    }
    int result = max_price[n];
    delete []max_price;
    return result;
}

void cut_rod_asc_seq(Rod *p, int n){
    int *max_price = new int[n + 1]{0};
    int *comb_lens = new int[n + 1]{0};
    int q;
    for (int i = 1; i <= n; ++i) {
        q = 0;
        for (int j = 0; (j <= 10) && (j < i); ++j) {
            if (q < max_price[i - j - 1] + p[j].price){
                q = max_price[i - j - 1] + p[j].price;
                comb_lens[i] = p[j].len;
            }
        }
        max_price[i] = q;
    }
    int j;
    for (int i = n; i > 0; i -= j) {
        j = comb_lens[i];
        std::cout << j << ' ';
    }
    std::cout << '\n';
    delete []max_price;
}

int main() {
    Rod rods[] = {{1, 1}, {2, 5}, {3, 8}, {4, 9}, {5, 10},
                  {6, 17}, {7, 17}, {8, 20}, {9, 24}, {10, 30}};
    //std::cout << cut_rod_recursive(rods, 15) << '\n';
    int n = 0;
    std::cin >> n;
    //std::cout << cut_rod_memoization(rods, n) << '\n';
    std::cout << cut_rod_asc(rods, n) << '\n';
    cut_rod_asc_seq(rods, n);
}