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
    void topological_sort();
};

void Graph::addEdge(int i, int j) {
    adjList[i].push_back(j);
}

void Graph::topological_sort() {
    vector<int> indegree(n+1, 0);
    list<int> queue;

    for(int i = 1; i <= n; i++) {
        for(int &j : adjList[i])  indegree[j]++;
    }
    for(int i = 1; i <= n; i++)  if(indegree[i] == 0)  queue.push_back(i);
    while(!queue.empty()) {
        int s = queue.front();
        cout << s << '\t';
        queue.pop_front();
        for(int &j : adjList[s]) {
            indegree[j]--;
            if(indegree[j] == 0)  queue.push_back(j);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Graph g(8);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(1, 5);
    g.addEdge(2, 3);
    g.addEdge(2, 8);
    g.addEdge(3, 6);
    g.addEdge(4, 6);
    g.addEdge(4, 8);
    g.addEdge(5, 8);
    g.addEdge(6, 7);
    g.addEdge(7, 8);
    g.topological_sort();
    return 0;
}