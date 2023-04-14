#include <bits/stdc++.h>
using namespace std;

int V;

void print_solution(int distance[]) {
    cout << "Vertex\tDistance from source" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << "\t\t" << distance[i] << endl;
    }
}

int* belman(int** graph, int src) {
    int distance[V];

    for (int i = 0; i < V; i++) {
        distance[i] = INT_MAX;
    }

    distance[src] = 0;

    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (distance[u] != INT_MAX && graph[u][v] && distance[u] + graph[u][v] < distance[v]) {
                    distance[v] = distance[u] + graph[u][v];
                }
            }
        }
    }

    int* distance_from_src = new int[V];
    for (int i = 0; i < V; i++) {
        distance_from_src[i] = distance[i];
    }

    return distance_from_src;
}

int main() {
    cout << "Enter the number of vertices: ";
    cin >> V;

    int** graph = new int*[V];
    for (int i = 0; i < V; i++) {
        graph[i] = new int[V];
    }

    cout << "Enter the adjacency matrix: " << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> graph[i][j];
        }
    }

    int src;
    cout << "Enter the source vertex: ";
    cin >> src;

    int* distance_from_src = belman(graph, src);
    print_solution(distance_from_src);

    return 0;
}