#include <bits/stdc++.h>
#define MATRIX_COUNT 10
using namespace std;

class Matrix {
   public:
    int** m;
    int row;
    int col;

    Matrix(int r, int c) {
        m = new int*[r];
        for (int i = 0; i < r; i++) {
            m[i] = new int[c];
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
};

void print_array(int* a, int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) {
        if (i == n - 1)
            cout << a[i];
        else
            cout << a[i] << ", ";
    }
    cout << "]" << endl;
}

int* order_matrices_in_range(int num, int min, int max) {
    int* p = new int[num + 1];
    srand(time(0));
    for (int i = 0; i <= num; i++) {
        p[i] = rand() % (max - min + 1) + min;
    }
    return p;
}

string optimal_parenthesization(Matrix* s, int i, int j) {
    if (i == j) {
        return "M" + to_string(i);

    } else {
        return "(" + optimal_parenthesization(s, i, s->m[i][j]) + " " +
               optimal_parenthesization(s, s->m[i][j] + 1, j) + ")";
    }
}

string matrix_chain(int* p, int n, Matrix* m, Matrix* s) {
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
    int* p = order_matrices_in_range(MATRIX_COUNT, 15, 46);

    cout << "\np[i] = ";
    print_array(p, MATRIX_COUNT + 1);
    cout << endl;

    Matrix** M = new Matrix*[MATRIX_COUNT + 1];

    for (int i = 1; i <= MATRIX_COUNT; i++) {
        M[i] = new Matrix(p[i - 1], p[i]);
        M[i]->fill_random_in_range(0, 1);
        cout << "Order of M" << i << " is (" << M[i]->row << ", " << M[i]->col
             << ")" << endl;
        Matrix::print(M[i]);
    }

    Matrix* m = new Matrix(MATRIX_COUNT + 1, MATRIX_COUNT + 1);
    Matrix* s = new Matrix(MATRIX_COUNT + 1, MATRIX_COUNT + 1);

    string optimum_inorder = matrix_chain(p, MATRIX_COUNT, m, s);

    cout << "\nCost matrix" << endl;
    Matrix::print(m, true, 8);

    cout << "\nParenthesization Matrix" << endl;
    Matrix::print(s, true);

    cout << "Optimal parenthesization : " << optimum_inorder << endl;

    return 0;
}