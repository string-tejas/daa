#include <bits/stdc++.h>
using namespace std;

long normal_mul_count = 0;
long strass_mul_count = 0;

bool is_power_of_two(int n) {
    if (n == 0) return true;
    return ceil(log2(n)) == floor(log2(n));
}

int** new_matrix(int n) {
    int** m = new int*[n];
    for (int i = 0; i < n; i++) {
        m[i] = new int[n];
    }
    return m;
}

int** get_random_matrix(int n) {
    int** m = new_matrix(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[i][j] = rand() % 10;
        }
    }

    return m;
}

void print_matrix(int** m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << left << setw(4) << m[i][j] << "  ";
        }
        cout << endl;
    }
}

int** normal_mm(int** a, int** b, int n) {
    int** c = new_matrix(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += a[i][k] * b[k][j];
                normal_mul_count++;
            }
            c[i][j] = sum;
        }
    }

    return c;
}

// basic operation required for strassens

int** mat_add(int** a, int** b, int n) {
    int** c = new_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    return c;
}

int** mat_sub(int** a, int** b, int n) {
    int** c = new_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] - b[i][j];
        }
    }
    return c;
}

int** strassens_mm(int** a, int** b, int n) {
    if (n == 1) {
        int** c = new_matrix(n);
        c[0][0] = a[0][0] * b[0][0];
        strass_mul_count++;

        return c;
    } else {
        int** c = new_matrix(n);
        int k = n / 2;

        // sub matrices initialization
        int** A11 = new_matrix(k);
        int** A12 = new_matrix(k);
        int** A21 = new_matrix(k);
        int** A22 = new_matrix(k);
        int** B11 = new_matrix(k);
        int** B12 = new_matrix(k);
        int** B21 = new_matrix(k);
        int** B22 = new_matrix(k);

        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                A11[i][j] = a[i][j];
                A12[i][j] = a[i][k + j];
                A21[i][j] = a[k + i][j];
                A22[i][j] = a[k + i][k + j];
                B11[i][j] = b[i][j];
                B12[i][j] = b[i][k + j];
                B21[i][j] = b[k + i][j];
                B22[i][j] = b[k + i][k + j];
            }
        }

        // calculations

        int** P1 = strassens_mm(A11, mat_sub(B12, B22, k), k);
        int** P2 = strassens_mm(mat_add(A11, A12, k), B22, k);
        int** P3 = strassens_mm(mat_add(A21, A22, k), B11, k);
        int** P4 = strassens_mm(A22, mat_sub(B21, B11, k), k);
        int** P5 = strassens_mm(mat_add(A11, A22, k), mat_add(B11, B22, k), k);
        int** P6 = strassens_mm(mat_sub(A12, A22, k), mat_add(B21, B22, k), k);
        int** P7 = strassens_mm(mat_sub(A11, A21, k), mat_add(B11, B12, k), k);

        int** C11 = mat_sub(mat_add(mat_add(P5, P4, k), P6, k), P2, k);
        int** C12 = mat_add(P1, P2, k);
        int** C21 = mat_add(P3, P4, k);
        int** C22 = mat_sub(mat_sub(mat_add(P5, P1, k), P3, k), P7, k);

        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                c[i][j] = C11[i][j];
                c[i][j + k] = C12[i][j];
                c[k + i][j] = C21[i][j];
                c[k + i][k + j] = C22[i][j];
            }
        }
        return c;
    }
}

int main() {
    int n;
    int** a;
    int** b;

    cout << "Enter matrix dimension: ";
    cin >> n;

    if (!is_power_of_two(n)) {
        cout << "The order of matrix must be a power of 2!\n";
        exit(EXIT_FAILURE);
    }

    cout << "\nGenerating random matrix A: \n";
    a = get_random_matrix(n);
    print_matrix(a, n);

    cout << "\nGenerating random matrix B: \n";
    b = get_random_matrix(n);
    print_matrix(b, n);

    int** c_n = normal_mm(a, b, n);

    cout << "\nResultant Matrix AB using normal multiplication: \n";
    print_matrix(c_n, n);

    cout << "\nResultant Matrix AB using strassen's multiplication: \n";
    int** c_s = strassens_mm(a, b, n);
    print_matrix(c_s, n);

    cout << "\n\nMultiplication required for normal multiplication: "
         << normal_mul_count << endl;
    cout << "Multiplication required for strassens multiplication: "
         << strass_mul_count << endl;

    return 0;
}
