#include <climits>
#include <iomanip>
#include <iostream>
#define v 5
using namespace std;

// find the index of the minimum distance
int minimum_dist(int dist[], int n, bool visited[]) {
    int min_dist = INT_MAX, index;

    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] <= min_dist) {
            min_dist = dist[i];
            index = i;
        }
    }
    return index;
}

int* dijkstra(int graph[v][v], int n, int src) {
    int* dist = new int[v];
    bool visited[n];

    // set initial distance to infinity
    // and initialize visited array
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    // distance from src to src is 0
    dist[src] = 0;

    for (int i = 0; i < n; i++) {
        // find index with minimum distance
        int m = minimum_dist(dist, n, visited);
        visited[m] = true;

        for (int i = 0; i < n; i++) {
            bool reachable_by_src = dist[m] != INT_MAX;
            bool path_exists_to_i = graph[m][i] > 0;
            bool new_shortest = dist[m] + graph[m][i] < dist[i];

            if (!visited[i] && reachable_by_src && path_exists_to_i &&
                new_shortest) {
                dist[i] = dist[m] + graph[m][i];
            }
        }
    }

    return dist;
}

void print_graph(int graph[][v], int n) {
    cout << "Graph: \n" << endl;
    cout << "   ";

    char ch = 'A';

    for (int i = 0; i < n; i++) {
        cout << setw(3) << ch << " ";
        ch = (char)((int)ch + 1);
    }

    cout << endl;

    ch = 'A';

    for (int i = 0; i < n; i++) {
        cout << ch << "  ";
        for (int j = 0; j < n; j++) {
            cout << setw(3) << graph[i][j] << " ";
        }
        ch = (char)((int)ch + 1);

        cout << endl;
    }
}

int main() {
    int graph[v][v] = {{0, 10, 3, 0, 0},
                       {0, 0, 1, 2, 0},
                       {0, 4, 0, 8, 2},
                       {0, 0, 0, 0, 7},
                       {0, 0, 0, 9, 0}};

    print_graph(graph, v);

    cout << endl;

    int* dist = dijkstra(graph, v, 0);

    cout << "Vertex\t\tDistance from source" << endl;

    char ch = 'A';
    for (int i = 0; i < v; i++) {
        cout << ch << "\t\t\t" << dist[i] << endl;
        ch = (char)((int)ch + 1);
    }
    return 0;
}