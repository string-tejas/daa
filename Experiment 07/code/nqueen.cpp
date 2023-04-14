#include <iostream>
using namespace std;

int sol_count = 0;

int** create_chessboard(int n) {
    int** chessboard = new int*[n];
    for (int i = 0; i < n; i++) {
        chessboard[i] = new int[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            chessboard[i][j] = 0;
        }
    }
    return chessboard;
}

void print_chessboard(int** chessboard, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (chessboard[i][j] == 1) {
                cout << "Q ";
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }
}

bool is_safe(int** chessboard, int row, int col, int n) {
    // check if there is a queen in the same column
    for (int i = 0; i < row; i++) {
        if (chessboard[i][col] == 1) {
            return false;
        }
    }

    // check if there is a queen in the upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (chessboard[i][j] == 1) {
            return false;
        }
    }

    // check if there is a queen in the upper right diagonal
    for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
        if (chessboard[i][j] == 1) {
            return false;
        }
    }

    return true;
}

void solve_nqueen(int** chessboard, int row, int n) {
    if (row == n) {
        cout << "Solution " << ++sol_count << ":" << endl;
        print_chessboard(chessboard, n);
        cout << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (is_safe(chessboard, row, i, n)) {
            chessboard[row][i] = 1;
            solve_nqueen(chessboard, row + 1, n);
            chessboard[row][i] = 0;
        }
    }
}
int main() {
    int n;
    
    cout << "Enter the number of queens: ";
    cin >> n;
    int** chessboard = create_chessboard(n);
    solve_nqueen(chessboard, 0, n);
    
    if (sol_count == 0) {
        cout << "No solution found." << endl;
    }
    return 0;
}