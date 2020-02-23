#include<bits/stdc++.h>
using namespace std;

class Graph {
    int n;
    vector<int> *adjList;
public:
    int dfs_number = 0;
    Graph(int n) {
        this->n = n;
        adjList = new vector<int>[n+1];
    }
    void addEdge(int i, int j);
    bool isCyclic(int source);
    void dfs(int source, vector<int> &visited, vector<int> &parents, vector<int> &pre_numbers, vector<int> &post_numbers);
};

void Graph::addEdge(int i, int j) {
    adjList[i].push_back(j);
}

bool Graph::isCyclic(int source) {
    vector<int> visited(n+1, 0);
    vector<int> parents(n+1, -1);
    vector<int> pre_numbers(n+1, 0);
    vector<int> post_numbers(n+1, 0);

    dfs(source, visited, parents, pre_numbers, post_numbers);
    post_numbers[source] = dfs_number;

    for(int i = 1; i <= n; i++) {
        for(auto j = adjList[i].begin(); j != adjList[i].end(); j++) {
            if(pre_numbers[i] > pre_numbers[*j] && post_numbers[i] < post_numbers[*j])  return true;
        }
    }
    return false;
}

void Graph::dfs(int source, vector<int> &visited, vector<int> &parents, vector<int> &pre_numbers, vector<int> &post_numbers) {
    vector<int>::iterator itr;
    visited[source] = 1;
    pre_numbers[source] = dfs_number++;

    for(itr = adjList[source].begin(); itr != adjList[source].end(); itr++) {
        if(!visited[*itr]) {
            dfs(*itr, visited, parents, pre_numbers, post_numbers);
            parents[*itr] = source;
            post_numbers[*itr] = dfs_number++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Graph g(8);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 6);
    g.addEdge(2, 5);
    g.addEdge(3, 4);
    g.addEdge(4, 1);
    g.addEdge(4, 8);
    g.addEdge(5, 6);
    g.addEdge(5, 7);
    g.addEdge(5, 8);
    g.addEdge(6, 2);
    g.addEdge(6, 7);
    g.addEdge(8, 7);
    g.isCyclic(1) ? cout << "Cycle(s) present.\n" : cout << "Cycle(s) not present.\n";
    return 0;
}