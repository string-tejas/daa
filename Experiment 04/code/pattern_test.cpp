#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    // (1,2) (2,3) ... ... (9, 10)
    // (1,3) (2,4) ... (8, 10)
    // .... ....
    // (1, 10)

    int t = 1;
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j + t <= n; j++) {
            cout << "(" << j << ", " << j + t << ")"
                 << "   ";
        }
        cout << endl;
        t++;
    }

    return 0;
}