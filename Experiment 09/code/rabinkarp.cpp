#include <bits/stdc++.h>
using namespace std;

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

bool compare(string str, string substr, int start) {
    for (int i = 0; i < substr.length(); i++) {
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
            if (compare(str, substr, i)) {
                cout << "Substring found at index " << i << endl;
            } else {
                spurious_hits++;
            }
        }
    }

    cout << "\nSpurious hits: " << spurious_hits << endl;
}

int main() {
    string str, substr;
    srand(time(0));
    cout << "Enter a string: ";
    cin >> str;

    cout << "Enter a substring: ";
    cin >> substr;

    int prime;
    cout << "Enter a prime number (0 for random): ";
    cin >> prime;

    if (prime == 0) {
        prime = gen_random_prime(100000);
        cout << "Random prime number generated: " << prime << endl;
    } else if (!is_prime(prime)) {
        cout << "Not a prime number" << endl;
        return 0;
    }

    cout << endl << "Applying Rabin-Karp algorithm" << endl;

    rabin_karp(str, substr, prime);

    return 0;
}