#include<bits/stdc++.h>
using namespace std;

void fix_heap_down(vector<int> &heap, int index) {
    while((2*index+1 <= heap.size()-1 && 2*index+2 <= heap.size()-1) && (heap[index] > heap[2*index+1] || heap[index] > heap[2*index+2])) {
        if(heap[2*index+1] <= heap[2*index+2]) {
            swap(heap[index], heap[2*index+1]);
            index = 2*index+1;
        } else {
            swap(heap[index], heap[2*index+2]);
            index = 2*index+2;
        }
    }
    if(2*index+1 <= heap.size()-1 && 2*index+2 > heap.size()-1) {
        if(heap[index] > heap[2*index+1])  swap(heap[index], heap[2*index+1]);
    }
}

int delete_min(vector<int> &heap) {
    int root = heap[0];
    heap[0] = heap[heap.size()-1];
    if(heap.size() != 1)  heap.pop_back();
    fix_heap_down(heap, 0);
    return root;
}

void heapify(vector<int> &heap) {
    int leaves = ceil(heap.size()/2);
    for(int i = heap.size()-leaves-1; i >= 0; i--)  fix_heap_down(heap, i);
}

void heap_sort(vector<int> &heap) {
    vector<int> sorted;
    heapify(heap);
    int n = heap.size();
    for(int i = 1; i <= n; i++)  sorted.push_back(delete_min(heap));

    cout << "Values after heap_sort(): ";
    for(int val : sorted)  cout << val << " "; cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int val;
    vector<int> heap;
    cout << "Enter values in the heap (and -1 to stop): ";
    cin >> val;
    while(val != -1) {
        heap.push_back(val);
        cin >> val;
    }
    heap_sort(heap);
    return 0;
}