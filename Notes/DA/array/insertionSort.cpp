#include <iostream>
using namespace std;

void insertion_sort(int *a, int n) {
    int i, j, t;
    for (i = 1; i < n; i++) {
        t = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > t) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = t;
    }
}

void insertion_sort_v2(int *a, int n) {
    int i, j, t;
    for (i = 1; i < n; i++) {
        t = a[i];
        j = i;
        while (j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            --j;
        }
        a[j] = t;
    }
}

int main() {
    int a[] = {5, 1, 8, 3, 4, 6, 2, 7};
    int n = sizeof(a) / sizeof(a[0]);
    insertion_sort(a, n);
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    int b[] = {5, 1, 8, 3, 4, 6, 2, 7};
    insertion_sort_v2(b, n);
    for (int i = 0; i < n; i++) {
        cout << b[i] << " ";
    }
    cout << endl;
    return 0;
}