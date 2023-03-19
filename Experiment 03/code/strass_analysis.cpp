#include <bits/stdc++.h>
using namespace std;

long normal_mul_count = 0;
long strass_mul_count = 0;

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
    // sequentially increase n with respect to power of 2
    // store the number of multiplication required in csv file
    int n = 1;
    ofstream fout("../csv/multiplication_analysis.csv");

    fout << "n,normal,strassens\n";

    cout << "Starting analysis!\n";

    for (int i = 0; i < 9; i++) {
        normal_mul_count = 0;
        strass_mul_count = 0;

        cout << "Calculating multiplication of order " << n << endl;

        int** a = get_random_matrix(n);
        int** b = get_random_matrix(n);

        normal_mm(a, b, n);
        strassens_mm(a, b, n);

        fout << n << "," << normal_mul_count << "," << strass_mul_count << "\n";
        n = n * 2;
    }

    cout << "\nAnalysis Data stored in csv/multiplication_analysis.csv\n";

    return 0;
}
