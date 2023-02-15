#include <stdio.h>

#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

double insertion_comparision = 0.0;
double selection_comparision = 0.0;

void insertion_sort(int* arr, int size) {
    for (int i = 1; i < size; i++) {
        int current = arr[i];
        int j = i - 1;
        while (j >= 0 && current < arr[j]) {
            arr[j + 1] = arr[j];
            j--;
            insertion_comparision++;
        }
        arr[j + 1] = current;
    }
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void selection_sort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        int i_min = i;
        for (int j = i + 1; j < size; j++) {
            selection_comparision++;
            if (arr[j] < arr[i_min]) {
                i_min = j;
            }
        }
        if (i != i_min) {
            swap(arr[i], arr[i_min]);
        }
    }
}

int digits(int num) {
    return num == 0 ? 1 : floor(log10(abs(num))) + 1;
}

int main() {
    int arr_ins[100000];
    int arr_sel[100000];
    ifstream nums("random_numbers.txt");
    ofstream output("../csv/sort_analysis.csv");
    output << "block_size,insertion,selection\n";

    for (int i = 1; i <= 100000; i++) {
        int val = 0;
        nums >> val;
        arr_ins[i] = val;
        arr_sel[i] = val;
    }

    // 1000 blocks of 100 numbers
    for (int i = 1; i <= 1000; i++) {
        // print 10 values at index 10000, 20000, ...
        int index = i * 100;
        if (index % 10000 == 0 && index != 100000) {
            cout << "\nPrinting 10 values from index " << index << endl;
            for (int t = 0; t < 10; t++) {
                cout << index + t << " : " << arr_ins[index + t] << "\n";
            }
        }

        // insertion
        auto ins_start = chrono::high_resolution_clock::now();
        insertion_sort(arr_ins, i * 100);
        auto ins_end = chrono::high_resolution_clock::now();
        chrono::duration<double> ins_time = (ins_end - ins_start);

        // selection
        auto sel_start = chrono::high_resolution_clock::now();
        selection_sort(arr_sel, i * 100);
        auto sel_end = chrono::high_resolution_clock::now();
        chrono::duration<double> sel_time = (sel_end - sel_start);

        output << i * 100 << "," << ins_time.count() << "," << sel_time.count() << "\n";
    }

    cout << "Sorting completed !" << endl;

    cout << "\nSmallest Number = " << arr_ins[0] << "\tDigits = " << digits(arr_ins[0]) << endl;
    cout << "Largest Number = " << arr_ins[99999] << "\tDigits = " << digits(arr_ins[99999]) << endl;

    printf("Insertion sort comparision count: %.0lf\n", insertion_comparision);
    printf("Selection sort comparision count: %.0lf\n", selection_comparision);

    return 0;
}