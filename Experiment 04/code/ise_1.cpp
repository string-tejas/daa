#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

class Matrix {
   public:
    ull** m;
    int row;
    int col;

    Matrix(int r, int c) {
        m = new ull*[r];
        for (int i = 0; i < r; i++) {
            m[i] = new ull[c];
        }

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                m[i][j] = 0;
            }
        }

        row = r;
        col = c;
    }

    void fill_random_in_range(int min, int max) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                m[i][j] = rand() % (max - min + 1) + min;
            }
        }
    }

    static void print(Matrix* matrix, bool skip_zero = false, int w = 1) {
        int start = skip_zero ? 1 : 0;
        for (int i = start; i < matrix->row; i++) {
            for (int j = start; j < matrix->col; j++) {
                cout << left << setw(w) << matrix->m[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    static ull mul_count;
    static Matrix* multiply(Matrix* a, Matrix* b) {
        Matrix* c = new Matrix(a->row, b->col);

        for (int i = 0; i < a->row; i++) {
            for (int j = 0; j < b->col; j++) {
                ull sum = 0;
                for (int k = 0; k < a->col; k++) {
                    sum += a->m[i][k] * b->m[k][j];
                    mul_count++;
                }
                c->m[i][j] = sum;
            }
        }
        return c;
    }
};

ull Matrix::mul_count = 0;

ull fuid(ull n) {
    ull res = 0;
    res = ceil(abs(sin(n) * 100));
    return res;
}

void print_array(ull* a, int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) {
        if (i == n - 1)
            cout << a[i];
        else
            cout << a[i] << ", ";
    }
    cout << "]" << endl;
}

string optimal_parenthesization(Matrix* s, int i, int j) {
    if (i == j) {
        return "M" + to_string(i);

    } else {
        return "(" + optimal_parenthesization(s, i, s->m[i][j]) + "*" +
               optimal_parenthesization(s, s->m[i][j] + 1, j) + ")";
    }
}

string matrix_chain(ull* p, int n, Matrix* m, Matrix* s) {
    int t = 1;
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j + t <= n; j++) {
            // j and (j + t) are indices of m
            // k = j to (j + t) - 1
            int min = INT_MAX;
            for (int k = j; k <= j + t - 1; k++) {
                int cost = m->m[j][k] + m->m[k + 1][j + t] +
                           p[j - 1] * p[k] * p[j + t];

                if (cost < min) {
                    min = cost;
                    m->m[j][j + t] = min;
                    s->m[j][j + t] = k;
                }
            }
        }
        t++;
    }

    return optimal_parenthesization(s, 1, n);
}

int main() {
    cout << "Enter last 6 digits of your roll number: ";
    ull roll;
    cin >> roll;

    ull* p = new ull[6];
    for (int i = 0; i < 6; i++) {
        p[i] = fuid(roll + i);
    }

    cout << "p = ";
    print_array(p, 6);

    Matrix* m = new Matrix(6, 6);
    Matrix* s = new Matrix(6, 6);

    string optimum_inorder = matrix_chain(p, 5, m, s);


    cout << "\nCost matrix" << endl;
    Matrix::print(m, true, 8);

    cout << "\nParenthesization Matrix" << endl;
    Matrix::print(s, true);

    
    cout << "Optimal parenthesization : " << optimum_inorder << endl;

    return 0;

}