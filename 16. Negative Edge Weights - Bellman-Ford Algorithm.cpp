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
    void bellman_ford(int source);
};

void Graph::addEdge(int u, int v, int weight) {
    adjList[u].push_back(v);
    weights[u][v] = weight;
    infinite_weight += weight;
}

void Graph::bellman_ford(int source) {
    vector<int> distance(n+1, infinite_weight+1);

    distance[source] = 0;
    for(int i = 1; i <= n-1; i++) {
        for(int u = 1; u <= n; u++) {
            for(auto itr = adjList[u].begin(); itr != adjList[u].end(); itr++) {
                if(distance[u] + weights[u][*itr] < distance[*itr])  distance[*itr] = distance[u] + weights[u][*itr];
            }
        }
    }
    for(int i = 1; i <= n; i++)  cout << "Node " << i << ": " << distance[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Graph g(8);
    g.addEdge(1,2,10);
    g.addEdge(1,8,8);
    g.addEdge(2,6,2);
    g.addEdge(3,2,1);
    g.addEdge(3,4,1);
    g.addEdge(4,5,3);
    g.addEdge(5,6,-1);
    g.addEdge(6,3,-2);
    g.addEdge(7,2,-4);
    g.addEdge(7,6,-1);
    g.addEdge(8,7,1);
    g.bellman_ford(1);
    return 0;
}