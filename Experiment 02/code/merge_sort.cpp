#include <bits/stdc++.h>
using namespace std;

void print_array(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// l to m (inclusive)
// m + 1 to h (inclusive)
void merge(int* arr, int l, int m, int h) {
    int n1 = m - l + 1;
    int n2 = h - m;

    int* l1 = new int[n1 + 1];
    int* l2 = new int[n2 + 1];

    l1[n1] = INT_MAX;
    l2[n2] = INT_MAX;

    int i1 = 0;
    int i2 = 0;

    for (int i = l; i <= m; i++) {
        l1[i1++] = arr[i];
    }

    for (int i = m + 1; i <= h; i++) {
        l2[i2++] = arr[i];
    }

    i1 = 0;
    i2 = 0;

    for (int i = l; i <= h; i++) {
        arr[i] = l1[i1] <= l2[i2] ? l1[i1++] : l2[i2++];
    }

    delete l1;
    delete l2;
}

void merge_sort(int* arr, int l, int h) {
    if (l < h) {
        int mid = (l + h) / 2;

        merge_sort(arr, l, mid);
        merge_sort(arr, mid + 1, h);

        merge(arr, l, mid, h);
    }
}

int main() {
    int arr[] = {1, 3, 20, 40, 2, 10, 50, 60, 5};
    int size = sizeof(arr) / sizeof(int);

    print_array(arr, size);

    merge_sort(arr, 0, size - 1);

    print_array(arr, size);

    return 0;
}