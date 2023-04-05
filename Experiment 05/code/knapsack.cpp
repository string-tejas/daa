#include <iostream>
using namespace std;

// * fractional knapsack using greedy method

struct Result {
    float total_profit;
    float total_weight;

    float *io_array;

    Result() {
        total_profit = 0;
        total_weight = 0;
        io_array = nullptr;
    }
};

struct RatioIndex {
    int index;
    float r;

    RatioIndex() {
        index = -1;
        r = 0;
    }
};

void sort_descending(RatioIndex **a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i]->r < a[j]->r) {
                RatioIndex *temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

void print_array(float *a, int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            cout << a[i] << " ]";
        } else {
            cout << a[i] << ", ";
        }
    }
    cout << endl;
}

void print_array(int *a, int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            cout << a[i] << " ]";
        } else {
            cout << a[i] << ", ";
        }
    }
    cout << endl;
}
void print_array(RatioIndex **a, int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            cout << "(" << a[i]->r << ", " << a[i]->index << ")"
                 << " ]";
        } else {
            cout << "(" << a[i]->r << ", " << a[i]->index << ")"
                 << ", ";
        }
    }
    cout << endl;
}

Result *knap_sack_greedy(int W, int n, int weight[], int profit[]) {
    float *io = new float[n];
    RatioIndex **ratio = new RatioIndex *[n];

    // get ratio of profit to weight
    for (int i = 0; i < n; i++) {
        ratio[i] = new RatioIndex();
        ratio[i]->r = (float)profit[i] / weight[i];
        ratio[i]->index = i;
    }

    // sort ratio in descending order
    sort_descending(ratio, n);

    int try_w = 0;
    float total_profit = 0;

    for (int i = 0; i < n; i++) {
        int index = ratio[i]->index;
        try_w += weight[index];
        io[index] = 1;

        if (try_w > W) {
            try_w -= weight[index];
            int space_needed = W - try_w;
            float portion_taken = (float)space_needed / weight[index];
            io[index] = portion_taken;
            total_profit += portion_taken * profit[index];
        } else {
            total_profit += profit[index];
        }
    }

    Result *res = new Result;
    res->io_array = io;
    res->total_profit = total_profit;
    res->total_weight = try_w;

    return res;
}

int main() {
    int capacity;

    cout << "\nEnter capacity of the bag: ";
    cin >> capacity;

    int items;
    cout << "Enter number of Items: ";
    cin >> items;

    int *weight = new int[items];
    int *profit = new int[items];

    cout << "Enter weight and value of the " << items << " items" << endl;

    for (int i = 0; i < items; i++) {
        cout << "Item " << i + 1 << " : ";
        cin >> weight[i];
        cin >> profit[i];
    }

    // test input
    // int items = 3;
    // int weight[] = {20, 30, 40};
    // int profit[] = {40, 20, 30};

    cout << "\nWeight: ";

    print_array(weight, items);

    cout << "\nProfit: ";
    print_array(profit, items);

    Result *r = knap_sack_greedy(capacity, items, weight, profit);

    cout << "\nTake the following : ";
    print_array(r->io_array, items);

    cout << "\nTotal weight : " << r->total_weight;
    cout << "\nTotal profit : " << r->total_profit;

    return 0;
}