#include <bits/stdc++.h>
using namespace std;

int V;

int parent[20];

int min_distance(int distance[], bool visited[]) {
    int min = INT_MAX;
    int min_index = 0;

    for (int i = 0; i < V; i++) {
        if (!visited[i] && distance[i] <= min) {
            min = distance[i];
            min_index = i;
        }
    }

    return min_index;
}

void print_solution(int distance[]) {
    cout << "Vertex\tDistance from source" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << "\t\t" << distance[i] << endl;
    }
}

int* dijkstras(int **graph, int src) {
    int distance[V];
    bool visited[V];

    for (int i = 0; i < V; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    distance[src] = 0;

    for (int i = 0; i < V - 1; i++) {
        int u = min_distance(distance, visited);

        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    int *distance_from_src = new int[V];
    for (int i = 0; i < V; i++) {
        distance_from_src[i] = distance[i];
    }

    return distance_from_src;

}

void print_path(int src, int dest) {
    if (dest == src) {
        cout << src << " ";
        return;
    }
    print_path(src, parent[dest]);
    cout << dest << " ";
}

int main() {
    cout << "Enter the number of vertices: ";
    cin >> V;

    int **graph = new int*[V];
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

    int *distance_from_src = dijkstras(graph, src);

    print_solution(distance_from_src);

    cout << "\nShortest Paths: " << endl;
    for (int i = 0; i < V; i++) {
        cout << src << " -> " << i << ": ";
        print_path(src, i);
        cout << endl;
    }

    return 0;
}