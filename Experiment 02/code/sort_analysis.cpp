#include <bits/stdc++.h>

#include <chrono>
#include <fstream>
using namespace std;

void print_array(int* a, int size) {
    for (int i = 0; i < size; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

void merge(int* arr, int l, int m, int h) {
    int left_size = m - l + 1;
    int right_size = h - m;

    int left[left_size];
    int right[right_size];

    int x = 0;
    int y = 0;
    int z = l;

    for (int i = l; i <= m; i++) {
        left[x++] = arr[i];
    }
    for (int i = m + 1; i <= h; i++) {
        right[y++] = arr[i];
    }

    x = y = 0;

    while (x < left_size && y < right_size) {
        arr[z++] = left[x] <= right[y] ? left[x++] : right[y++];
    }

    while (x < left_size) {
        arr[z++] = left[x++];
    }

    while (y < right_size) {
        arr[z++] = right[y++];
    }
}

void merge_sort(int* arr, int l, int h) {
    if (l < h) {
        int mid = (l + h) / 2;
        merge_sort(arr, l, mid);
        merge_sort(arr, mid + 1, h);
        merge(arr, l, mid, h);
    }
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(int* a, int l, int h) {
    // pivot selection: last element
    int pivot = h;
    int low = l;
    int high = h - 1;

    while (low < high) {
        while (a[low] <= a[pivot] && low < h) {
            low++;
        }

        while (a[high] > a[pivot] && high >= l) {
            high--;
        }

        if (low < high) {
            swap(a[low], a[high]);
        }
    }

    if (a[low] > a[pivot])
        swap(a[low], a[pivot]);

    return low;
}

void quick_sort(int* a, int l, int h) {
    if (l < h) {
        int pivot = partition(a, l, h);
        quick_sort(a, l, pivot - 1);
        quick_sort(a, pivot + 1, h);
    }
}

int main() {
    int* arr_mer = new int[100000];
    int* arr_qui = new int[100000];

    ifstream nums("random_numbers.txt");
    ofstream output("../csv/sort_analysis.csv");
    output << "block_size,merge,quick\n";

    for (int i = 1; i <= 100000; i++) {
        int val = 0;
        nums >> val;
        arr_mer[i] = val;
        arr_qui[i] = val;
    }

    for (int i = 1; i <= 1000; i++) {
        // merge sort
        auto merge_start = chrono::high_resolution_clock::now();
        merge_sort(arr_mer, 0, i * 100 - 1);
        auto merge_end = chrono::high_resolution_clock::now();
        chrono::duration<double> merge_time = (merge_end - merge_start);

        // quick sort
        auto quick_start = chrono::high_resolution_clock::now();
        quick_sort(arr_qui, 0, i * 100 - 1);
        auto quick_end = chrono::high_resolution_clock::now();
        chrono::duration<double> quick_time = (quick_end - quick_start);

        output << i * 100 << "," << merge_time.count() << ","
               << quick_time.count() << "\n";
    }

    cout << "Sorting completed !" << endl;

    return 0;
}