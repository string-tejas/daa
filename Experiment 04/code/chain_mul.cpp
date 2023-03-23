#include <bits/stdc++.h>
using namespace std;

class Matrix {
   public:
    float** m;
    int row;
    int col;

    Matrix(int r, int c) {
        m = new float*[r];
        for (int i = 0; i < r; i++) {
            m[i] = new float[c];
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

    static long mul_count;
    static Matrix* multiply(Matrix* a, Matrix* b) {
        Matrix* c = new Matrix(a->row, b->col);

        for (int i = 0; i < a->row; i++) {
            for (int j = 0; j < b->col; j++) {
                float sum = 0;
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

long Matrix::mul_count = 0;

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

int* gen_matrix_orders_in_range(int num, int min, int max) {
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
        return "(" + optimal_parenthesization(s, i, s->m[i][j]) + "*" +
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

string to_postfix(string infix) {
    string postfix = "";
    vector<char> stack;

    for (int i = 0; i < infix.size(); i++) {
        char ch = infix[i];
        if (ch == '(') {
            stack.push_back(ch);
        } else if (ch == '*') {
            stack.push_back('*');
        } else if (ch == ')') {
            while (stack[stack.size() - 1] != '(') {
                postfix = postfix + stack.back();
                stack.pop_back();
            }
            stack.pop_back();
        } else {
            if (ch == 'M') {
                postfix += " ";
            }
            postfix = postfix + ch;
        }
    }

    while (stack.size() != 0) {
        char pop = stack.back();
        postfix = postfix + pop;
        stack.pop_back();
    }

    return postfix;
}

long count_normal = 0;

Matrix* eval_matrix_normal_mul(string postfix, Matrix** m_arr) {
    vector<Matrix*> eval;

    Matrix::mul_count = 0;

    for (int i = 0; i < postfix.size(); i++) {
        char ch = postfix[i];

        if (ch == 'M' || ch == ' ') {
            continue;
        }
        if (ch == '*') {
            Matrix* b = eval.back();
            eval.pop_back();

            Matrix* a = eval.back();
            eval.pop_back();

            Matrix* c = Matrix::multiply(a, b);

            eval.push_back(c);

        } else if (ch >= '1' || ch <= '9') {
            int index = ch - '0';
            if (ch == '1' && postfix[i + 1] == '0') {
                index = 10;
                i++;
            }
            eval.push_back(m_arr[index]);
        }
    }
    return eval.back();
}

int main() {
    int MATRIX_COUNT = 0;

    cout << "Enter number of matrices (<= 10) : ";
    cin >> MATRIX_COUNT;

    int* p = gen_matrix_orders_in_range(MATRIX_COUNT, 15, 46);

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

    string optimum_postfix = to_postfix(optimum_inorder);
    cout << "Postfix expression : " << optimum_postfix << endl;

    cout << "\nResult Of Multiplication : " << endl;

    Matrix::print(eval_matrix_normal_mul(optimum_postfix, M));

    cout << "Estimated Multiplication count: " << m->m[1][m->col - 1] << endl;
    cout << "Actual Multiplication count: " << Matrix::mul_count << endl;

    return 0;
}