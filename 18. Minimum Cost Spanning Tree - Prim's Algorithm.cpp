#include<bits/stdc++.h>
using namespace std;

typedef struct Edge {
    int u, v;
    Edge(int u, int v) {
        this->u = u, this->v = v;
    }
} edge;

class Graph {
    int n, infinite_weight = 0;
    vector<int> *adjList;
    vector<vector<int>> weights;
    vector<edge> spanning_tree_edges;
public:
    Graph(int n) {
        this->n = n;
        adjList = new vector<int>[n+1];
        weights.resize(n+1, vector<int>(n+1, 0));
    }
    void addEdge(int u, int v, int weight);
    void prims();
};

void Graph::addEdge(int u, int v, int weight) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
    weights[u][v] = weights[v][u] = weight;
    infinite_weight += weight;
}

void Graph::prims() {
    vector<int> visited(n+1, 0);
    vector<int> distance(n+1, infinite_weight+1);
    vector<int> neighbors(n+1, -1);

    visited[1] = 1;
    for(auto itr = adjList[1].begin(); itr != adjList[1].end(); itr++)  distance[*itr] = weights[1][*itr], neighbors[*itr] = 1;

    for(int i = 2; i <= n; i++) {
        int u, min = infinite_weight+1;
        for(int j = 1; j <= n; j++)  if(!visited[j] && distance[j] < min)  min = distance[j], u = j;
        visited[u] = 1;
        spanning_tree_edges.push_back(edge(neighbors[u], u));
        for(auto itr = adjList[u].begin(); itr != adjList[u].end(); itr++) {
            if(weights[u][*itr] < distance[*itr]) {
                distance[*itr] = weights[u][*itr];
                neighbors[*itr] = u;
            }
        }
    }

    int cost = 0;
    cout << "\nMinimum Cost Spanning Tree - ";
    for(edge e: spanning_tree_edges)  cout << "(" << e.u << ", " << e.v << ") ", cost += weights[e.u][e.v]; cout << endl;
    cout << "Cost - " << cost << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Graph g(7);
    g.addEdge(1,2,10);
    g.addEdge(1,3,18);
    g.addEdge(2,3,6);
    g.addEdge(2,5,20);
    g.addEdge(3,4,70);
    g.addEdge(5,6,10);
    g.addEdge(5,7,10);
    g.addEdge(6,7,5);
    g.prims();
    return 0;
}