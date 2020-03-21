#include<bits/stdc++.h>
using namespace std;

class Graph {
    int n, infinite_weight = 0;
    vector<int> *adjList;
    vector<vector<int>> weights;
public:
    int *VertexToHeap, *HeapToVertex;
    Graph(int n) {
        this->n = n;
        adjList = new vector<int>[n+1];
        weights.resize(n+1, vector<int>(n+1, 0));
        VertexToHeap = new int[n+1];
        HeapToVertex = new int[n];
    }
    void fix_heap_down(vector<int> &heap, int index);
    void fix_heap_up(vector<int> &heap, int index);
    int delete_min(vector<int> &heap, vector<int> &distance);
    void update_heap(vector<int> &heap, int heap_node, int newDist);
    void addEdge(int u, int v, int weight);
    void dijkstra(int source);
};

void Graph::addEdge(int u, int v, int weight) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
    weights[u][v] = weights[v][u] = weight;
    infinite_weight += weight;
}

void Graph::dijkstra(int source) {
    vector<int> visited(n+1, 0);
    vector<int> distance(n+1, infinite_weight+1);
    vector<int> heap(n, infinite_weight+1);
    for(int i = 1; i <= n; i++)  VertexToHeap[i] = i-1;
    for(int i = 0; i < n; i++)  HeapToVertex[i] = i+1;

    heap[source-1] = 0;
    for(int i = 1; i <= n; i++) {
        int u = delete_min(heap, distance);
        visited[u] = 1;
        for(auto itr = adjList[u].begin(); itr != adjList[u].end(); itr++) {
            if(!visited[*itr] && distance[u] + weights[u][*itr] < heap[VertexToHeap[*itr]]) {
                update_heap(heap, VertexToHeap[*itr], distance[u] + weights[u][*itr]);
            }
        }
    }

    for(int i = 1; i <= n; i++)  cout << "Node " << i << ": " << distance[i] << '\n';
}

void Graph::fix_heap_down(vector<int> &heap, int index) {
    while((heap[index] > heap[2*index+1] || heap[index] > heap[2*index+2]) && (2*index+1 <= heap.size()-1 || 2*index+2 <= heap.size()-1)) {
        if(heap[2*index+1] <= heap[2*index+2]) {
            swap(heap[index], heap[2*index+1]);
            swap(VertexToHeap[HeapToVertex[index]], VertexToHeap[HeapToVertex[2*index+1]]);
            swap(HeapToVertex[index], HeapToVertex[2*index+1]);
            index = 2*index+1;
        } else {
            swap(heap[index], heap[2*index+2]);
            swap(VertexToHeap[HeapToVertex[index]], VertexToHeap[HeapToVertex[2*index+2]]);
            swap(HeapToVertex[index], HeapToVertex[2*index+2]);
            index = 2*index+2;
        }
    }
}

void Graph::fix_heap_up(vector<int> &heap, int index) {
    int parent = floor((index-1)/2);
    while(heap[index] < heap[parent] && index != 0) {
        swap(heap[parent], heap[index]);
        swap(VertexToHeap[HeapToVertex[index]], VertexToHeap[HeapToVertex[parent]]);
        swap(HeapToVertex[index], HeapToVertex[parent]);
        index = parent;
        parent = floor((index-1)/2);
    }
}

int Graph::delete_min(vector<int> &heap, vector<int> &distance) {
    int root_vertex = HeapToVertex[0];
    int rootDist = heap[0];
    distance[root_vertex] = rootDist;
    heap[0] = heap[heap.size()-1];
    VertexToHeap[HeapToVertex[heap.size()-1]] = 0;
    HeapToVertex[0] = HeapToVertex[heap.size()-1];
    if(heap.size() != 1)  heap.pop_back();

    int index = 0;
    fix_heap_down(heap, index);
    return root_vertex;
}

void Graph::update_heap(vector<int> &heap, int node, int newDist) {
    int oldDist = heap[node];
    heap[node] = newDist;
    int index = node;
    if(newDist > oldDist)  fix_heap_down(heap, index);
    else if(newDist < oldDist)  fix_heap_up(heap, index);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Graph g(6);
    g.addEdge(1,2,90);
    g.addEdge(1,3,25);
    g.addEdge(1,4,50);
    g.addEdge(2,3,50);
    g.addEdge(2,5,6);
    g.addEdge(2,6,1);
    g.addEdge(3,4,24);
    g.addEdge(3,6,8);
    g.addEdge(4,5,12);
    g.dijkstra(1);
    return 0;
}