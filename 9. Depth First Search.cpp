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
    void dfs_util(int source);
    void dfs(int source, vector<int> &visited, vector<int> &parents, vector<int> &pre_numbers, vector<int> &post_numbers);
};

void Graph::addEdge(int i, int j) {
    adjList[i].push_back(j);
    adjList[j].push_back(i);
}

void Graph::dfs_util(int source) {
    vector<int> visited(n+1, 0);
    vector<int> parents(n+1, -1);
    vector<int> pre_numbers(n+1, 0);
    vector<int> post_numbers(n+1, 0);

    dfs(source, visited, parents, pre_numbers, post_numbers);
    post_numbers[source] = dfs_number;

    cout << "\n\nNode\tParent\tPre-Number\tPost-Number\n";
    for(int i = 1; i <= n; i++)  cout << i << "\t\t" << parents[i] << "\t\t" << pre_numbers[i] << "\t\t\t" << post_numbers[i] << '\n';
}

void Graph::dfs(int source, vector<int> &visited, vector<int> &parents, vector<int> &pre_numbers, vector<int> &post_numbers) {
    vector<int>::iterator itr;
    visited[source] = 1;
    cout << source << '\t';
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
    cout << "\nDepth First Traversal of the following Undirected Graph (starting from node 4) is as follows: \n";
    g.dfs_util(4);
    return 0;
}