void swap(int &a, int &b);

void qsort(int *arr, int n) {
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
}
