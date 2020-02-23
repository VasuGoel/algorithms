#include<bits/stdc++.h>
using namespace std;

typedef struct Edge {
    int u, v, weight;
    Edge(int u, int v, int weight) {
        this->u = u, this->v = v, this->weight = weight;
    }
} edge;

bool comparator(edge u, edge v) {
    return u.weight < v.weight;
}

class Graph {
    int n;
    vector<edge> edges;
    vector<edge> spanning_tree_edges;
public:
    Graph(int n) {
        this->n = n;
    }
    void addEdge(int u, int v, int weight);
    void kruskal();
};

void Graph::addEdge(int u, int v, int weight) {
    edges.push_back(edge(u, v, weight));
}

void Graph::kruskal() {
    vector<int> components(n+1);
    std::iota(components.begin(), components.end(), 0);

    sort(edges.begin(), edges.end(), &comparator);

    int i = 0;
    while(spanning_tree_edges.size() < n-1) {
        edge chosen = edges[i++];
        int find_u = components[chosen.u], find_v = components[chosen.v];
        if(find_u != find_v) {
            spanning_tree_edges.push_back(chosen);
            for(int j = 1; j <= n; j++)  if(components[j] == find_v)  components[j] = find_u;
        }
    }

    int cost = 0;
    cout << "\nMinimum Cost Spanning Tree - ";
    for(edge e: spanning_tree_edges)  cout << "(" << e.u << ", " << e.v << ") ", cost += e.weight; cout << endl;
    cout << "Cost - " << cost << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Graph g(9);
    g.addEdge(1,2,4);
    g.addEdge(1,8,8);
    g.addEdge(2,3,8);
    g.addEdge(2,8,11);
    g.addEdge(3,4,7);
    g.addEdge(3,6,4);
    g.addEdge(3,9,2);
    g.addEdge(4,5,9);
    g.addEdge(4,6,14);
    g.addEdge(5,6,10);
    g.addEdge(6,7,2);
    g.addEdge(7,8,1);
    g.addEdge(7,9,6);
    g.addEdge(8,9,7);
    g.kruskal();
    return 0;
}