#include <chrono>
#include <fstream>
#include <iostream>

void insertion_sort(int* arr, int size) {
    for (int i = 1; i < size; i++) {
        int current = arr[i];
        int j = i - 1;
        while (j >= 0 && current < arr[j]) {
            arr[j + 1] = arr[j];
            j--;
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
            if (arr[j] < arr[i_min]) {
                i_min = j;
            }
        }
        if (i != i_min) {
            swap(arr[i], arr[i_min]);
        }
    }
}

int main() {
    int* arr_ins = new int[100000];
    int* arr_sel = new int[100000];
    std::ifstream nums("nums.txt");
    std::ofstream output("sort_time.csv");
    output << "block_size,insertion,selection\n";

    for (int i = 1; i <= 100000; i++) {
        int val = 0;
        nums >> val;
        arr_ins[i] = val;
        arr_sel[i] = val;
    }

    // 1000 blocks of 100 numbers
    for (int i = 1; i <= 1000; i++) {
        auto ins_start = std::chrono::high_resolution_clock::now();
        insertion_sort(arr_ins, i * 100);
        auto ins_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> ins_time = (ins_end - ins_start);

        auto sel_start = std::chrono::high_resolution_clock::now();
        selection_sort(arr_sel, i * 100);
        auto sel_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> sel_time = (sel_end - sel_start);

        // std::cout << "\nBlock : " << i * 100 << "\n";
        // std::cout << "insertion sort : " << ins_time.count() << "\t"
        //           << "selection sort : " << sel_time.count() << "\n";

        output << i * 100 << "," << ins_time.count() << "," << sel_time.count() << "\n";
    }

    std::cout << "Sorting completed !";

    return 0;
}