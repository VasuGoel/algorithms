#include<bits/stdc++.h>
using namespace std;

class Graph {
    int n, infinite_weight = 0;
    vector<int> *adjList;
    vector<vector<int>> weights;
public:
    Graph(int n) {
        this->n = n;
        adjList = new vector<int>[n+1];
        weights.resize(n+1, vector<int>(n+1, 0));
    }
    void addEdge(int u, int v, int weight);
    void dijkstra(int source);
};

void Graph::addEdge(int u, int v, int weight) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
    weights[u][v] = weights[v][u] = weight;
    infinite_weight += weight;
}

void Graph::dijkstra(int source) {
    vector<int> visited(n+1, 0);
    vector<int> distance(n+1, infinite_weight+1);

    distance[source] = 0;
    for(int i = 1; i <= n; i++) {
        int u, min = infinite_weight+1;
        for(int j = 1; j <= n; j++)  if(!visited[j] && distance[j] < min)  min = distance[j], u = j;
        visited[u] = 1;
        for (auto itr = adjList[u].begin(); itr != adjList[u].end(); itr++) {
            if(distance[u] + weights[u][*itr] < distance[*itr])  distance[*itr] = distance[u] + weights[u][*itr];
        }
    }
    for(int i = 1; i <= n; i++)  cout << "Node " << i << ": " << distance[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Graph g(7);
    g.addEdge(1, 2,10);
    g.addEdge(1, 3, 80);
    g.addEdge(2, 3, 6);
    g.addEdge(2, 5, 20);
    g.addEdge(3, 4, 70);
    g.addEdge(5, 6, 50);
    g.addEdge(5, 7, 10);
    g.addEdge(6, 7, 5);
    g.dijkstra(1);
    return 0;
}