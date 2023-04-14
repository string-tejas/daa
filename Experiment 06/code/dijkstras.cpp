#include <bits/stdc++.h>
using namespace std;

int V;

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
        // Initialize all distances as infinite and visited as false
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    // Distance of source vertex from itself is always 0
    distance[src] = 0;

    for (int i = 0; i < V - 1; i++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = min_distance(distance, visited);

        // Mark the picked vertex as processed
        visited[u] = true;

        // Update distance value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            // Update distance[v] only if it is not in visited, there is an edge from u to v, and total weight of path from src to v through u is smaller than current value of distance[v]
            if (!visited[v] && graph[u][v] && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
            }
        }
    }

    int *distance_from_src = new int[V];
    for (int i = 0; i < V; i++) {
        distance_from_src[i] = distance[i];
    }

    return distance_from_src;

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

    return 0;
}