#include<bits/stdc++.h>
using namespace std;

class Graph {
    int n;
    vector<int> *adjList;
    vector<int> *connected_components;
public:
    int components = 0;
    Graph(int n) {
        this->n = n;
        adjList = new vector<int>[n+1];
        connected_components = new vector<int>[n];
    }
    void addEdge(int u, int v);
    void find_components();
    void dfs(int source, vector<int> &visited);
    int count_museums(int k, vector<int> &museums);
};

void Graph::addEdge(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

void Graph::find_components() {
    vector<int> visited(n+1, 0);
    for(int i = 1; i <= n; i++)  if(!visited[i])  dfs(i, visited),  components++;
}

void Graph::dfs(int source, vector<int> &visited) {
    vector<int>::iterator itr;
    visited[source] = 1;
    connected_components[components].push_back(source);
    for(itr = adjList[source].begin(); itr != adjList[source].end(); itr++) {
        if(!visited[*itr]) {
            dfs(*itr, visited);
        }
    }
}

int Graph::count_museums(int k, vector<int> &museums) {
    vector<int> total_museums;
    for(int i = 0; i < components; i++) {
        int total = 0;
        for(int j: connected_components[i])  total += museums[j];
        total_museums.push_back(total);
    }
    int total = 0;
    vector<int>::iterator itr;
    for(int i = 0; i < k; i++) {
        if(i % 2 == 0)  itr = max_element(total_museums.begin(), total_museums.end());
        else   itr = min_element(total_museums.begin(), total_museums.end());
        total += *itr;
        total_museums.erase(itr);
    }
    return total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k, u, v, x;
    cin >> n >> m >> k;
    Graph g(n);
    for(int i = 0; i < m; i++)  cin >> u >> v,  g.addEdge(u, v);
    g.find_components();
    vector<int> museums(n+1, 0);
    for(int i = 1; i <= n; i++)  cin >> x, museums[i] = x;
    (k <= g.components) ? cout << g.count_museums(k, museums) << '\n' : cout << -1 << '\n';
    return 0;
}