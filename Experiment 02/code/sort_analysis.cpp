#include <bits/stdc++.h>
#include <stdio.h>

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;

double merge_comparision = 0.0;
double quick_comparision = 0.0;

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
        merge_comparision++;
    }

    while (x < left_size) {
        arr[z++] = left[x++];
        merge_comparision++;
    }

    while (y < right_size) {
        arr[z++] = right[y++];
        merge_comparision++;
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
    int pivot = h;
    int low = l;
    int high = h - 1;

    while (low < high) {
        while (a[low] <= a[pivot] && low < h) {
            quick_comparision++;
            low++;
        }

        while (a[high] > a[pivot] && high >= l) {
            quick_comparision++;
            high--;
        }

        if (low < high) {
            quick_comparision++;
            swap(a[low], a[high]);
        }
    }

    if (a[low] > a[pivot])
        swap(a[low], a[pivot]);

    return low;
}

int partition_random(int* a, int l, int h) {
    srand(time(NULL));
    int random = l + rand() % (h - l);
    swap(a[random], a[h]);

    return partition(a, l, h);
}

void quick_sort(int* a, int l, int h) {
    if (l < h) {
        int pivot = partition(a, l, h);
        quick_sort(a, l, pivot - 1);
        quick_sort(a, pivot + 1, h);
    }
}

int digits(int num) {
    return num == 0 ? 1 : floor(log10(abs(num))) + 1;
}

int main() {
    int arr_mer[100000];
    int arr_qui[100000];

    ifstream nums("random_numbers.txt");
    ofstream output("../csv/sort_analysis.csv");
    ofstream comparison("../csv/comparison.csv");

    output << "block_size,merge,quick\n";
    comparison << "block_no,merge,quick\n";

    for (int i = 1; i <= 100000; i++) {
        nums >> arr_mer[i];
        arr_qui[i] = arr_mer[i];
    }

    for (int i = 1; i <= 1000; i++) {
        // print 10 values at index 10000, 20000, ...
        int index = i * 100;
        if (index % 10000 == 0 && index != 100000) {
            cout << "\nPrinting 10 values from index " << index << endl;
            for (int t = 0; t < 10; t++) {
                cout << index + t << " : " << arr_mer[index + t] << "\n";
            }
        }

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

        comparison << i << "," << merge_comparision << "," << quick_comparision << "\n";
    }

    cout << "\nSorting completed !" << endl;

    cout << "\nSmallest Number = " << arr_mer[0] << "\tDigits = " << digits(arr_mer[0]) << endl;
    cout << "Largest Number = " << arr_mer[99999] << "\tDigits = " << digits(arr_mer[99999]) << endl;

    printf("Merge sort comparision count: %.0lf\n", merge_comparision);
    printf("Quick sort comparision count: %.0lf\n", quick_comparision);

    return 0;
}