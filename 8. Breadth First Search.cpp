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
    void bfs(int source);
};

void Graph::addEdge(int i, int j) {
    adjList[i].push_back(j);
    adjList[j].push_back(i);
}

void Graph::bfs(int source) {
    vector<int> visited(n+1, 0);
    vector<int>::iterator itr;
    vector<int> parents(n+1, -1);
    vector<int> levels(n+1, 0);
    list<int> queue;

    visited[source] = 1;
    queue.push_back(source);

    while(!queue.empty()) {
        int s = queue.front();
        cout << s << "\t";
        queue.pop_front();

        for(itr = adjList[s].begin(); itr != adjList[s].end(); itr++) {
            if(!visited[*itr]) {
                visited[*itr] = 1;
                queue.push_back(*itr);
                levels[*itr] = 1 + levels[s];
                parents[*itr] = s;
            }
        }
    }

    cout << "\n\nNode\tLevel\tParent\n";
    for(int i = 1; i <= n; i++)  cout << i << "\t\t" << levels[i] << "\t\t" << parents[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Graph g(10);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(4, 5);
    g.addEdge(4, 8);
    g.addEdge(5, 6);
    g.addEdge(5, 7);
    g.addEdge(6, 7);
    g.addEdge(6, 8);
    g.addEdge(6, 9);
    g.addEdge(8, 9);
    g.addEdge(9, 10);
    cout << "\nBreadth First Traversal of the following Undirected Graph (starting from node 1) is as follows: \n";
    g.bfs(1);
    return 0;
}