#include<bits/stdc++.h>
using namespace std;

class Graph {
    int n, infinite_weight = 0;
    vector<vector<vector<int>>> weights;
public:
    Graph(int n) {
        this->n = n;
        weights.resize(2, vector<vector<int>>(n+1, vector<int>(n+1, 0)));
    }
    void addEdge(int u, int v, int weight);
    void floyd_warshall();
};

void Graph::addEdge(int u, int v, int weight) {
    weights[0][u][v] = weight;
    infinite_weight += weight;
}

void Graph::floyd_warshall() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++)  if(i != j && weights[0][i][j] == 0)  weights[0][i][j] = infinite_weight+1;
    }

    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(k % 2 == 1)  weights[1][i][j] = min(weights[0][i][j], weights[0][i][k] + weights[0][k][j]);
                else  weights[0][i][j] = min(weights[1][i][j], weights[1][i][k] + weights[1][k][j]);
            }
        }
    }

    int d = (n%2 == 0) ? 0 : 1;
    cout << "\nAll Pairs Shortest Paths for the following graph are as follows:\n\t";
    for(int i = 1; i <= n; i++)  cout << i << '\t'; cout << '\n';
    for(int i = 1; i <= n; i++) {
        cout << i << '\t';
        for(int j = 1; j <= n; j++)  (weights[d][i][j] != infinite_weight+1) ? cout << weights[d][i][j] << '\t' : cout << "INF\t"; cout << '\n';
    }
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
    g.floyd_warshall();
    return 0;
}