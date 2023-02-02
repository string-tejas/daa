#include <math.h>
#include <stdio.h>

int fn_01(int n) {
    return n;
}

double fn_02(int n) {
    if (n <= 0) return -1.0;
    return log2(n);
}

double fn_03(int n) {
    if (n <= 0) return -1.0;
    if (log2(n) == 0) return -1.0;
    return log2(log2(n));
}

double fn_04(int n) {
    if (n <= 0) return -1.0;
    return n * log2(n);
}

double fn_05(int n) {
    if (n <= 0) return -1.0;
    return pow(log2(n), log2(n));
}

double fn_06(int n) {
    if (n <= 0) return -1.0;
    return sqrt(log2(n));
}

double fn_07(int n) {
    if (n <= 0) return -1.0;
    return pow(2, log2(n));
}

// (lg n)!
double fn_08(int n) {
    if (n <= 0) return -1.0;
    double fact = 1;
    for (int i = 1; i <= ceil(log2(n)); i++) {
        fact *= i;
    }
    return fact;
}

double fn_09(int n) {
    if (n <= 0) return -1.0;

    return pow(sqrt(2), log2(n));
}

double fn_10(int n) {
    return n * n * n;
}

double fact(int n) {
    if (n == 0) return 1;
    double f = 1.0;
    for (int i = 1; i <= n; i++) {
        f = f * i;
    }
    return f;
}

int main() {
    FILE *fptr;
    // fptr = fopen("D://Tejas//College//sem4//daa//data.csv", "w");
    fptr = fopen("../csv/functions.csv", "w");

    fprintf(fptr, "i,n,lg n,lg(lg n),n*lg n,(lg n)^(lg n),sqrt(lg n),2^lg n,(lg n)!,sqrt(2)^lg n,n^3,n!\n");
    printf("\n  i |   n   lg n  lg(lg n)  n*lg n  (lg n)^(lg n)  sqrt(lg n)  2^lg n  (lg n)!  sqrt(2)^lg n   n^3\n\n");

    for (int i = 0; i <= 100; i++) {
        printf("%3d | %3d  %5.2f  %8.2f  %8.2f  %10.2f  %10.2f  %6.0f  %7.0f  %8.2f  %10.0f\n", i, fn_01(i), fn_02(i), fn_03(i), fn_04(i), fn_05(i), fn_06(i), fn_07(i), fn_08(i), fn_09(i), fn_10(i));

        fprintf(fptr, "%d,%d,%f,%f,%f,%f,%f,%.0f,%.0f,%f,%.0f", i, fn_01(i), fn_02(i), fn_03(i), fn_04(i), fn_05(i), fn_06(i), fn_07(i), fn_08(i), fn_09(i), fn_10(i));

        if (i <= 20) {
            fprintf(fptr, ",%0.f\n", fact(i));
        } else {
            fprintf(fptr, ",-\n");
        }
    }
    fclose(fptr);
    printf("\n\nFactorials: \n");
    for (int i = 0; i <= 20; i++) {
        printf("%2d! = %.0f\n", i, fact(i));
    }
    return 0;
}
