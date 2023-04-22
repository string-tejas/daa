#include <bits/stdc++.h>
using namespace std;

int c_count_naive = 0;
int c_count_rbkarp = 0;

int to_int(char c) { return c - 'a' + 1; }

bool is_prime(int n) {
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int gen_random_prime(int n) {
    int p = rand() % n;
    while (!is_prime(p)) {
        p = rand() % n;
    }
    return p;
}

bool compare(string str, string substr, int start, bool rabin_karp = false) {
    for (int i = 0; i < substr.length(); i++) {
        if (rabin_karp) {
            c_count_rbkarp++;
        } else {
            c_count_naive++;
        }
        if (str[start + i] != substr[i]) {
            return false;
        }
    }

    return true;
}

int s_hash(string str, int start, int n, int q) {
    int h = 0;
    int pow_10 = n;

    for (int i = 0; i < n; i++) {
        h += to_int(str[start + i]) * pow(10, pow_10);
        pow_10--;
    }
    h = h / 10;

    return h % q;
}

void naive_matching(string str, string substr) {
    int n = str.length();
    int m = substr.length();

    if (n < m) {
        cout << "Substring cannot be found\nOriginal String is smaller" << endl;
        return;
    }

    for (int i = 0; i <= n - m; i++) {
        if (compare(str, substr, i, false)) {
            cout << "Substring found at index " << i << endl;
        }
    }
}

void rabin_karp(string str, string substr, int q) {
    int n = str.length();
    int m = substr.length();

    if (n < m) {
        cout << "Substring cannot be found\nOriginal String is smaller" << endl;
        return;
    }

    int h_substr = s_hash(substr, 0, m, q);
    int spurious_hits = 0;

    for (int i = 0; i <= n - m; i++) {
        int h_str = s_hash(str, i, m, q);
        if (h_substr == h_str) {
            if (compare(str, substr, i, true)) {
                cout << "Substring found at index " << i << endl;
            } else {
                spurious_hits++;
            }
        }
    }

    cout << "\nSpurious hits: " << spurious_hits << endl;
}

int main() {
    string str = "aab", substr = "ab";
    srand(time(0));
    ofstream fout("../csv/analysis.csv");

    int prime = 0;

    if (prime == 0) {
        prime = gen_random_prime(100000);
        cout << "Random prime number generated: " << prime << endl;
    } else if (!is_prime(prime)) {
        cout << "Not a prime number" << endl;
        return 0;
    }

    fout << "Naive,Rabin-Karp" << endl;

    for (int i = 0; i < 50; i++) {
        c_count_naive = 0;
        c_count_rbkarp = 0;

        cout << endl << "Applying Naive algorithm" << endl;

        naive_matching(str, substr);

        cout << endl << "Applying Rabin-Karp algorithm" << endl;

        rabin_karp(str, substr, prime);
        cout << endl
             << "Number of comparisons in Naive algorithm: " << c_count_naive
             << endl;
        cout << "Number of comparisons in Rabin-Karp algorithm: "
             << c_count_rbkarp << endl;

        fout << c_count_naive << "," << c_count_rbkarp << endl;

        str = "aa" + str;
    }

    return 0;
}