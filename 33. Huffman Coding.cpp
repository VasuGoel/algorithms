#include<bits/stdc++.h>
using namespace std;

typedef struct Node {
    char alphabet;
    double frequency;
    Node *left, *right;
} node;

node *newNode(char alphabet, double frequency) {
    node *new_node = new node;
    new_node->alphabet = alphabet, new_node->frequency = frequency;
    return new_node;
}

void heapify(vector<node *> &, vector<char> &, vector<double> &);
void insert(vector<node *> &, node *);
node *delete_min(vector<node *> &);
node *huffman_tree(vector<node *> &);
void huffman_codes(node *, vector<int>);
void display_tree(node *);


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<node *> min_heap;
    vector<char> alphabets{'a', 'b', 'c', 'd', 'e'};
    vector<double> frequency{0.32, 0.25, 0.20, 0.18, 0.05};

    heapify(min_heap, alphabets, frequency);

    node *root = huffman_tree(min_heap);
    cout << "Huffman tree: \n";
    display_tree(root);

    vector<int> code;
    huffman_codes(root, code);
    return 0;
}

void heapify(vector<node *> &heap, vector<char> &alphabets, vector<double> &frequency) {
    for(int i = 0; i < alphabets.size(); i++)  insert(heap, newNode(alphabets[i], frequency[i]));
}

void insert(vector<node *> &heap, node *new_node) {
    heap.push_back(new_node);
    int index = heap.size()-1;
    int parent = floor((index-1)/2);
    while(heap[index]->frequency < heap[parent]->frequency && index != 0) {
        swap(heap[parent], heap[index]);
        index = parent;
        parent = floor((index-1)/2);
    }
}

node *delete_min(vector<node *> &heap) {
    node *root = heap[0];
    if(heap.size() == 1) {
        heap.pop_back();
        return root;
    }
    heap[0] = heap[heap.size()-1];
    heap.pop_back();
    int index = 0;
    while((2*index+1 <= heap.size()-1 && 2*index+2 <= heap.size()-1) && (heap[index]->frequency > heap[2*index+1]->frequency || heap[index]->frequency > heap[2*index+2]->frequency)) {
        if(heap[2*index+1]->frequency <= heap[2*index+2]->frequency) {
            swap(heap[index], heap[2*index+1]);
            index = 2*index+1;
        } else {
            swap(heap[index], heap[2*index+2]);
            index = 2*index+2;
        }
    }
    if(2*index+1 <= heap.size()-1 && 2*index+2 > heap.size()-1) {
        if(heap[index]->frequency > heap[2*index+1]->frequency)  swap(heap[index], heap[2*index+1]);
    }
    return root;
}

node *huffman_tree(vector<node *> &min_heap) {
    while(min_heap.size() != 1) {
        node *left = delete_min(min_heap);
        node *right = delete_min(min_heap);
        node *top = newNode('$', left->frequency + right->frequency);
        top->left = left, top->right = right;
        insert(min_heap, top);
    }
    return delete_min(min_heap);
}

void huffman_codes(node *tree, vector<int> code) {
    if(tree->left != nullptr) {
        code.push_back(0);
        huffman_codes(tree->left, code), code.pop_back();
    }
    if(tree->right != nullptr) {
        code.push_back(1);
        huffman_codes(tree->right, code), code.pop_back();
    }
    if(tree->left == nullptr && tree->right == nullptr) {
        cout << tree->alphabet << ": ";
        for(int i: code)  cout << i; cout << "\n";
    }
}

void display_tree(node *tree) {
    queue<node *> q;
    q.push(tree);
    while(!q.empty()) {
        int level_node_count = q.size();
        while(level_node_count--) {
            node *node = q.front();
            cout << "(" << node->alphabet << ", " << node->frequency << ") ";
            q.pop();
            if(node->left != nullptr)  q.push(node->left);
            if(node->right != nullptr) q.push(node->right);
        }
        cout << "\n";
    }
}