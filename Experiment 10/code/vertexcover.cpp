#include <bits/stdc++.h>
using namespace std;

struct Edge {
    char u;
    char v;

    Edge() {
        u = 0;
        v = 0;
    }

    Edge(char u, char v) {
        this->u = u;
        this->v = v;
    }
};

set<char> vertexCover(vector<Edge>& edges) {
    set<char> cover;
    vector<Edge> edges_copy = edges;
    srand(time(NULL));

    while (!edges_copy.empty()) {
        int i = rand() % edges_copy.size();
        Edge e = edges_copy[i];
        edges_copy.erase(edges_copy.begin() + i);

        cover.insert(e.u);
        cover.insert(e.v);

        cout << "Adding edge " << e.u << " " << e.v << "\n";
        for (int i = 0; i < edges_copy.size(); i++) {
            if (edges_copy[i].u == e.u || edges_copy[i].v == e.u ||
                edges_copy[i].u == e.v || edges_copy[i].v == e.v) {
                cout << "Removing edge " << edges_copy[i].u << " "
                     << edges_copy[i].v << "\n";
                edges_copy.erase(edges_copy.begin() + i);
                i--;
            }
        }
    }
    return cover;
}

int main() {
    cout << "Enter the number of edges then enter each edge in the format \"u "
            "v\" where u and v are vertices of the edge.\n";
    int n;
    cin >> n;
    vector<Edge> edges(n);
    for (int i = 0; i < n; i++) {
        char u, v;
        cin >> u >> v;
        edges[i] = Edge(u, v);
    }

    cout << "\nRunning Approximate Vertex Cover Algorithm...\n";
    set<char> cover = vertexCover(edges);
    cout << "\nVertex Cover: { ";
    for (char v : cover) {
        cout << v << ", ";
    }
    cout << "}\n" << endl;
    return 0;
}

// sample input
// 8
// a b
// b c
// c d
// c e
// d e
// d f
// d g
// e f