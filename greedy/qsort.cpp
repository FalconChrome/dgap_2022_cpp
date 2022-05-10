#include "qsort.h"
#include <iostream>

void swap(int &a, int &b){
    int c;
    c = a;
    a = b;
    b = c;
}

void reverse(int *arr, int n){
    for (int i = 0; i < n / 2; ++i) {
        swap(arr[i], arr[n - i - 1]);
    }
}


void qsort(int *arr, int n, bool reversed) {
    if (n < 2) {
        return;
    }
    int l = 0;
    int r = n - 1;
    int pivot = arr[0];

    do {
        while (arr[l] < pivot) {
            ++l;
        }
        while (arr[r] >= pivot and r > 0) {
            --r;
        }
        if (l < r) {
            swap(arr[l], arr[r]);
            ++l;
            --r;
        }
    } while (l < r);

    if (arr[r] <= pivot) {
        ++r;
    }

    qsort(arr, r);
    qsort(arr + r, n - r);

    if (reversed){
        reverse(arr, n);
    }
}

void print_array(int *arr, int n) {
    std::cout << "int Array[" << n << "]:" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << '\t';
    }
    std::cout << std::endl;
}


