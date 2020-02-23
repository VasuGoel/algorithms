#include<bits/stdc++.h>
using namespace std;

class Graph {
    int n;
    vector<int> *adjList;
    vector<int> *connected_components;
public:
    int component = 0;
    Graph(int n) {
        this->n = n;
        adjList = new vector<int>[n+1];
        connected_components = new vector<int>[n+1];
    }
    void addEdge(int i, int j);
    void find_components();
    void dfs(int source, vector<int> &visited);
};

void Graph::addEdge(int i, int j) {
    adjList[i].push_back(j);
    adjList[j].push_back(i);
}

void Graph::find_components() {
    vector<int> visited(n+1, 0);

    for(int i = 1; i <= n; i++) {
        if(!visited[i]) {
            dfs(i, visited);
            component++;
        }
    }

    cout << "\nNumber of Connected Components in the following graph: " << component << "\n\n";
    for(int i = 0; i < component; i++) {
        cout << "Component " << i+1 << ": ";
        for(int j : connected_components[i])  cout << j << '\t';
        cout << '\n';
    }
}

void Graph::dfs(int source, vector<int> &visited) {
    vector<int>::iterator itr;

    visited[source] = 1;
    connected_components[component].push_back(source);

    for(itr = adjList[source].begin(); itr != adjList[source].end(); itr++) {
        if(!visited[*itr]) {
            dfs(*itr, visited);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Graph g(12);
    g.addEdge(1, 2);
    g.addEdge(1, 5);
    g.addEdge(3, 4);
    g.addEdge(3, 7);
    g.addEdge(3, 8);
    g.addEdge(4, 8);
    g.addEdge(5, 9);
    g.addEdge(5, 10);
    g.addEdge(7, 8);
    g.addEdge(7, 11);
    g.addEdge(8, 11);
    g.addEdge(8, 12);
    g.addEdge(9, 10);
    g.find_components();
    return 0;
}