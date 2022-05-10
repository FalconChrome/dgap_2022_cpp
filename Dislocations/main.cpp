#include <iostream>
#include <random>
#include <fstream>
#define WRITEDATA true
#define ERASEDATA true
#define FDATA "./data11d"
using namespace std;

const int N = 200;

char field[N*N];
char new_field[N*N];
int dislocation[N*N];

random_device dev;
mt19937 rng(dev());

void write_data(int n, int k, int *c, int size){
    static ofstream out;
    out.open(FDATA, ios::app);
    if(out.is_open()){
        out << "((" << size << ", " << n << ", " << k << "), [";
        for (int i = 0; i < size; ++i) {
            out << c[i] << ", ";
        }
        out << "])" << endl;
    }
    out.close();
}

void swap(int &a, int &b){
    int c = a;
    a = b;
    b = c;
}

void swap(int* &a, int* &b){
    int *c = a;
    a = b;
    b = c;
}

template<class T> void copy_array(T src[N*N], T dest[N*N], int n){
    for (int i = 0; i < n; ++i) {
        dest[i] = src[i];
    }
}

template<class T> void print_array(T array[], int size, bool mute=false){
    if (not mute){
        cout << "int array[" << size << "]" << endl;
    }
    for (int i = 0; i < size; ++i){
        cout << array[i] << '\t';
    }
    cout << endl;
}

void print_table(char *array, int size_c, int size_r){
    cout << "int Table[" << size_r << " x " << size_c << "]\n";
    for (int i = 0; i < size_c; ++i) {
        cout << '\t' << i;
    }
    cout << endl;
    for (int i = 0; i < size_c; ++i) {
        cout << i * size_r << '\t';
        print_array(array + i * size_r, size_r, true);
    }
}


void fill_field(int n, int mark){
    for (int i = 0; i < n; ++i) {
        field[i] = mark;
    }
}

char minor_mark(int n, int k){
    if (2 * k < n * n){
        return 'O';
    }
    return '_';
}

char turn_mark(char mark){
    if (mark == ' '){
        return 'O';
    }
    return '_';
}

void gen_field(int n, int k){
    char mark = minor_mark(n, k); // 'O' if generating dl and '_' if gaps (atoms) between them
    if (mark == '_'){
        k = n - k;
    }
    fill_field(n, turn_mark(mark));

    uniform_int_distribution<int> dist(0, n - 1);
    int dl;
    for (int i = 0; i < k; ++i) {
        do {
            dl = dist(rng);
        } while (field[dl] == mark); // same mark means cell is taken
        dislocation[i] = dl;
        field[dl] = mark;
    }
}


bool on_bound(int n, int dl){
    int r = dl % n;
    return (dl < n) or (dl >= n * (n - 1)) or (r == 0) or (r == n - 1);
}

bool on_bound_1d(int n, int dl){
    return (dl == 0) or (dl == n - 1);
}

bool neighbours(int n, int dl){
    for (char c : {field[dl + 1], field[dl - 1], field[dl + n], field[dl - n]}){
        if (c != '_'){
            return true;
        }
    }
    return false;
}

bool neighbours_1d(int n, int dl){
    for (char c : {field[dl + 1], field[dl - 1]}){
        if (c != '_'){
            return true;
        }
    }
    return false;
}

bool stop_condition(int n, int dl){
    if (not on_bound(n, dl)){
        return neighbours(n, dl);
    }
    return true; // else on bound
}

bool stop_condition_1d(int n, int dl){
    if (not on_bound_1d(n, dl)){
        return neighbours_1d(n, dl);
    }
    return true; // else on bound
}

void move(int n, int i, auto dist){
    int dl = dislocation[i];
    int d = dist(rng);
    dl += ((d ^ 1) ? 1 : -1) * ((d ^ 2) ? n : 1);
    if (new_field[dl] == '_'){
        new_field[dislocation[i]] = '_';
        new_field[dl] = 'O';
        dislocation[i] = dl;
    }
}

void move_1d(int n, int i, auto dist){
    int dl = dislocation[i];
    int d = dist(rng);
    dl += ((d ^ 1) ? 1 : -1);
    if (new_field[dl] == '_'){
        new_field[dislocation[i]] = '_';
        new_field[dl] = 'O';
        dislocation[i] = dl;
    }
}

int run(int n, int k) {
    copy_array(field, new_field, n*n);
    uniform_int_distribution<int> dist(0, 3);
    int count = 0;
    while (k != 0){
        for (int i = k - 1; i >= 0; --i){
//            print_table(new_field, n, n);
//            cout << i << "\t\t" << dislocation[i] / n << "\t- " << dislocation[i] % n << endl;
            if (stop_condition(n, dislocation[i])){
                swap(dislocation[i], dislocation[k - 1]);
                new_field[dislocation[k - 1]] = 'x'; // mark that dl stopped
                --k;
                continue;
            }
            move(n, i, dist);
        }
        copy_array(new_field, field, n*n);
//        print_table(field, n, n);
        ++count;
    }
    return count;
}

int run_1d(int n, int k) {
    copy_array(field, new_field, n);
    uniform_int_distribution<int> dist(0, 3);
    int count = 0;
    while (k != 0){
        for (int i = k - 1; i >= 0; --i){
//            print_table(new_field, n, n);
//            cout << i << "\t\t" << dislocation[i] / n << "\t- " << dislocation[i] % n << endl;
            if (stop_condition_1d(n, dislocation[i])){
                swap(dislocation[i], dislocation[k - 1]);
                new_field[dislocation[k - 1]] = 'x'; // mark that dl stopped
                --k;
                continue;
            }
            move_1d(n, i, dist);
        }
        copy_array(new_field, field, n);
//        print_table(field, 1, n);
        ++count;
    }
    return count;
}

void iterate(int n, int k, int *c, int R){
    for (int i = 0; i < R; ++i) {
        gen_field(n*n, k);
//        cout << "Generated field:" << endl;
//        print_table(field, n, n);
//        print_array(dislocation, k);
        c[i] = run(n, k);
//        cout << c[i];
    }
}

void iterate_1d(int n, int k, int *c, int R){
    for (int i = 0; i < R; ++i) {
        gen_field(n, k);
//        cout << "Generated field:" << endl;
//        print_table(field, n, n);
//        print_array(dislocation, k);
        c[i] = run_1d(n, k);
//        cout << c[i];
    }
}

void run_all(int start = 1, int end = N){
    const int R = 10;
    int c[R];
    for (int n = start; n <= end; ++n) {
        for (int k = 0; k <= n*n; ++k) {
            iterate(n, k, c, R);
            if (WRITEDATA) {
                write_data(n, k, c, R);
            }
        }
        cout << n << '/' << end << endl;
    }
}

void runby1(int start = 1, int end = N){
    const int R = 500;
    int c[R];
    for (int n = start; n <= end; ++n) {
        iterate(n, 1, c, R);
        if (WRITEDATA) {
            write_data(n, 1, c, R);
        }
        cout << n << '/' << end << endl;
    }
}

void run_all_1d(int start = 1, int end = N){
    const int R = 10;
    int c[R];
    for (int n = start; n <= end; ++n) {
        for (int k = 0; k <= n; ++k) {
            iterate_1d(n, k, c, R);
            if (WRITEDATA) {
                write_data(n, k, c, R);
            }
        }
        cout << n << '/' << end << endl;
    }
}

void runby1_1d(int start = 1, int end = N){
    const int R = 500;
    int c[R];
    for (int n = start; n <= end; ++n) {
        iterate_1d(n, 1, c, R);
        if (WRITEDATA) {
            write_data(n, 1, c, R);
        }
        cout << n << '/' << end << endl;
    }
}


int main() {
    if (ERASEDATA){
        ofstream out(FDATA, ios::out);
        out.close();
    }
    if (WRITEDATA){
        (1, N);
    }
    int a, b;
    //cin >> a;
    runby1_1d(1, N);/*
    const int R = 10;
    int c[R];
    int n=8, k=50;
    cout << "Enter side of square and amount of dislocations: ";
    cin >> n >> k;
    iterate(n, k, c, R);
    print_array(c, R);
*/
//    print_array(dislocation, n);

    return 0;
}
