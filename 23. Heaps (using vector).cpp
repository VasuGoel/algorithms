#include<bits/stdc++.h>
using namespace std;

void insert(vector<int> &heap, int val) {
    heap.push_back(val);
    int index = heap.size()-1;
    int parent = floor((index-1)/2);
    while(heap[index] > heap[parent] && index != 0) {
        swap(heap[parent], heap[index]);
        index = parent;
        parent = floor((index-1)/2);
    }
}

int delete_max(vector<int> &heap) {
    int root = heap[0];
    heap[0] = heap[heap.size()-1];
    heap.pop_back();
    int index = 0;
    while((2*index+1 <= heap.size()-1 && 2*index+2 <= heap.size()-1) && (heap[index] < heap[2*index+1] || heap[index] < heap[2*index+2])) {
        if(heap[2*index+1] >= heap[2*index+2]) {
            swap(heap[index], heap[2*index+1]);
            index = 2*index+1;
        } else {
            swap(heap[index], heap[2*index+2]);
            index = 2*index+2;
        }
    }
    if(2*index+1 <= heap.size()-1 && 2*index+2 > heap.size()-1) {
        if(heap[index] < heap[2*index+1])  swap(heap[index], heap[2*index+1]);
    }
    return root;
}

void heapify(vector<int> &heap) {
    int val;
    cout << "Enter numbers to insert into heap (and -1 to stop): ";
    cin >> val;
    while(val != -1) {
        heap.push_back(val);
        cin >> val;
    }
    int leaves = ceil(heap.size()/2);
    for(int i = heap.size()-leaves-1; i >= 0; i--) {
        int index = i;
        while((2*index+1 <= heap.size()-1 && 2*index+2 <= heap.size()-1) && (heap[index] < heap[2*index+1] || heap[index] < heap[2*index+2])) {
            if(heap[2*index+1] >= heap[2*index+2]) {
                swap(heap[index], heap[2*index+1]);
                index = 2*index+1;
            } else {
                swap(heap[index], heap[2*index+2]);
                index = 2*index+2;
            }
        }
        if(2*index+1 <= heap.size()-1 && 2*index+2 > heap.size()-1) {
            if(heap[index] < heap[2*index+1])  swap(heap[index], heap[2*index+1]);
        }
    }
    cout << "Heap created.\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int choice;
    vector<int> heap;

    cout << "\n1. heapify()\t\t2. insert()\n3. delete_max()\t\t4. display_heap()\n5. EXIT\n";
    cout << "----------------------------------------\n";
    cout << "\nEnter your choice: ";
    cin >> choice;
    while(choice != 5) {
        switch(choice) {
            case 1: heapify(heap);
                break;

            case 2: int val;
                cout << "Enter number: ";
                cin >> val;
                insert(heap, val);
                cout << val << " inserted into the heap.\n";
                break;

            case 3: cout << delete_max(heap) << " deleted from the heap.\n";
                break;

            case 4: for(int i : heap)  cout << i << " ";
                cout << endl;
                break;

            case 5: return 0;

            default: cout << "Wrong choice!\n";
        }
        cout << "\nEnter your choice: ";
        cin >> choice;
    }
    return 0;
}