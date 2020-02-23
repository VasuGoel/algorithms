#include<bits/stdc++.h>
using namespace std;

class Graph {
    int n;
    vector<int> *adjList;
public:
    Graph(int n) {
        this->n = n;
        adjList = new vector<int>[n+1];
    }
    void addEdge(int i, int j);
    bool isCyclic();
    bool isCyclicUtil(int source, vector<int> &visited, int parent);
};

void Graph::addEdge(int i, int j) {
    adjList[i].push_back(j);
    adjList[j].push_back(i);
}

bool Graph::isCyclic() {
    vector<int> visited(n+1, 0);
    for(int i = 1; i <= n; i++) {
        if(!visited[i]) {
            if(isCyclicUtil(i, visited, -1))  return true;
        }
    }
    return false;
}

bool Graph::isCyclicUtil(int source, vector<int> &visited, int parent) {
    vector<int>::iterator itr;

    visited[source] = 1;
    for(itr = adjList[source].begin(); itr != adjList[source].end(); itr++) {
        if(visited[*itr] && *itr != parent)  return true;
        else if(!visited[*itr]) {
            if(isCyclicUtil(*itr, visited, source))  return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Graph g(5);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    g.isCyclic() ? cout << "\nCycle(s) present.\n" : cout << "\nCycle(s) not present.\n";
    return 0;
}