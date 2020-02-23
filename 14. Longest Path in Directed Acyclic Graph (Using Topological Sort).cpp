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
    void longest_path();
};

void Graph::addEdge(int i, int j) {
    adjList[i].push_back(j);
}

void Graph::longest_path() {
    vector<int> indegrees(n+1, 0);
    vector<int> longest_paths(n+1, 0);
    list<int> queue;

    for(int i = 1; i <= n; i++) {
        for(int &j : adjList[i])  indegrees[j]++;
    }
    for(int i = 1; i <= n; i++)  if(indegrees[i] == 0)  queue.push_back(i);
    while(!queue.empty()) {
        int s = queue.front();
        cout << s << "\t";
        queue.pop_front();
        for(int &j : adjList[s]) {
            indegrees[j]--;
            if(indegrees[j] == 0)  queue.push_back(j);
            longest_paths[j] = max(longest_paths[j], 1 + longest_paths[s]);
        }
    }

    cout << "\n\nNode\tLongest Path\n";
    for(int i = 1; i <= n; i++)  cout << i << "\t\t" << longest_paths[i] << "\n";
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
    cout << "\nTopological Ordering:\t";
    g.longest_path();
    return 0;
}