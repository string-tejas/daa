#include <bits/stdc++.h>
using namespace std;

int** create4x4Array() {
    int** arr = new int*[4];
    for (int i = 0; i < 4; i++) {
        arr[i] = new int[4];
    }
    return arr;
}

void input4x4Array(int** arr) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> arr[i][j];
        }
    }
}

void output4x4Array(int** arr) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << setw(3) << arr[i][j] << " ";
        }
        cout << endl;
    }
}

pair<int, int> find_empty_position(int** arr) {
    pair<int, int> pos;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (arr[i][j] == 0) {
                pos.first = i;
                pos.second = j;
                return pos;
            }
        }
    }
    return pos;
}

void swap(int** arr, pair<int, int> pos1, pair<int, int> pos2) {
    int temp = arr[pos1.first][pos1.second];
    arr[pos1.first][pos1.second] = arr[pos2.first][pos2.second];
    arr[pos2.first][pos2.second] = temp;
}

void move_up(int** arr) {
    pair<int, int> pos = find_empty_position(arr);
    if (pos.first == 0) {
        cout << "Can't move up" << endl;
    } else {
        swap(arr, pos, make_pair(pos.first - 1, pos.second));
    }
}

void move_down(int** arr) {
    pair<int, int> pos = find_empty_position(arr);
    if (pos.first == 3) {
        cout << "Can't move down" << endl;
    } else {
        swap(arr, pos, make_pair(pos.first + 1, pos.second));
    }
}

void move_left(int** arr) {
    pair<int, int> pos = find_empty_position(arr);
    if (pos.second == 0) {
        cout << "Can't move left" << endl;
    } else {
        swap(arr, pos, make_pair(pos.first, pos.second - 1));
    }
}

void move_right(int** arr) {
    pair<int, int> pos = find_empty_position(arr);
    if (pos.second == 3) {
        cout << "Can't move right" << endl;
    } else {
        swap(arr, pos, make_pair(pos.first, pos.second + 1));
    }
}

void move(int** arr, char c) {
    switch (c) {
        case 'u':
            move_up(arr);
            break;
        case 'd':
            move_down(arr);
            break;
        case 'l':
            move_left(arr);
            break;
        case 'r':
            move_right(arr);
            break;
        default:
            cout << "Invalid move" << endl;
    }
}

int misplaced(int** arr) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (arr[i][j] != (4 * i + j + 1) % 16) {
                count++;
            }
        }
    }
    return count;
}

bool can_move(int** arr, char c) {
    pair<int, int> pos = find_empty_position(arr);
    switch (c) {
        case 'u':
            return pos.first != 0;
        case 'd':
            return pos.first != 3;
        case 'l':
            return pos.second != 0;
        case 'r':
            return pos.second != 3;
        default:
            return false;
    }
    return true;
}

void solve15puzzle(int** arr) {
    int move_count = 0;
    int misplaced_count = misplaced(arr);
    int cost = 0;

    char prev_move = ' ';

    while (misplaced_count != 0) {
        move_count++;
        int cost_up = INT_MAX, cost_down = INT_MAX, cost_left = INT_MAX,
            cost_right = INT_MAX;

        if (prev_move != 'd' && can_move(arr, 'u')) {
            move(arr, 'u');
            cost_up = misplaced(arr) + move_count;
            move(arr, 'd');
        }

        if (prev_move != 'u' && can_move(arr, 'd')) {
            move(arr, 'd');
            cost_down = misplaced(arr) + move_count;
            move(arr, 'u');
        }

        if (prev_move != 'r' && can_move(arr, 'l')) {
            move(arr, 'l');
            cost_left = misplaced(arr) + move_count;
            move(arr, 'r');
        }

        if (prev_move != 'l' && can_move(arr, 'r')) {
            move(arr, 'r');
            cost_right = misplaced(arr) + move_count;
            move(arr, 'l');
        }

        cout << endl
             << "Costs: " << cost_up << " " << cost_down << " " << cost_left
             << " " << cost_right << endl;

        if (cost_up < cost_down && cost_up < cost_left &&
            cost_up < cost_right && can_move(arr, 'u')) {
            move(arr, 'u');
            prev_move = 'u';
            cost = cost_up;
        } else if (cost_down < cost_left && cost_down < cost_right &&
                   can_move(arr, 'd')) {
            move(arr, 'd');
            prev_move = 'd';
            cost = cost_down;
        } else if (cost_left < cost_right && can_move(arr, 'l')) {
            move(arr, 'l');
            prev_move = 'l';
            cost = cost_left;
        } else {
            move(arr, 'r');
            prev_move = 'r';
            cost = cost_right;
        }

        cout << endl << move_count << ") ";
        cout << "Move: " << prev_move;
        cout << "  Cost: " << cost << endl;

        output4x4Array(arr);
        misplaced_count = misplaced(arr);
        cout << endl;
    }
}

int main() {
    int** arr = create4x4Array();

    cout << "Enter inital state of 15 puzzle: " << endl;
    input4x4Array(arr);

    cout << "\n\nInitial state of 15 puzzle: " << endl;
    output4x4Array(arr);

    solve15puzzle(arr);

    return 0;
}