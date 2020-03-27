#include<bits/stdc++.h>
using namespace std;

typedef struct Node {
    int data;
    Node *parent, *left, *right;
} node;

node *tree = nullptr;
void create_binary_tree(node *&, vector<int> &);
void insert(node *&, int);
void display_tree(node *&);
int height(node *&);
bool isBalanced(node *&, int &);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> values{5, 3, 7, 1, 4, 6, 9, 2, 8, 10};
    create_binary_tree(tree, values);
    display_tree(tree);

    int height = 0;
    if(isBalanced(tree, height))  cout << "\nTree is height balanced.\n";
    else  cout << "\nTree is not height balanced.\n";
    return 0;
}

void create_binary_tree(node *&tree, vector<int> &values) {
    for(int val: values)  insert(tree, val);
}

void insert(node *&tree, int val) {
    node *new_node, *ptr, *preptr = nullptr;
    new_node = new node;
    new_node->data =  val, new_node->left = nullptr, new_node->right = nullptr;

    if(tree == nullptr) {
        tree = new_node;
        tree->parent = nullptr, tree->left = nullptr, tree->right = nullptr;
    } else {
        ptr = tree;
        while(ptr != nullptr) {
            preptr = ptr;
            if(val < ptr->data)  ptr = ptr->left;
            else  ptr = ptr->right;
        }
        if(val < preptr->data)  preptr->left = new_node;
        else  preptr->right = new_node;
        new_node->parent = preptr;
    }
}

void display_tree(node *&tree) {
    queue<node *> q;
    q.push(tree);
    while(!q.empty()) {
        int level_node_count = q.size();
        while(level_node_count--) {
            node *node = q.front();
            cout << node->data << " ";
            q.pop();
            if(node->left != nullptr)  q.push(node->left);
            if(node->right != nullptr) q.push(node->right);
        }
        cout << "\n";
    }
}

int height(node *&tree) {
    if(tree == nullptr)  return 0;
    return 1 + max(height(tree->left), height(tree->right));
}

// O(n^2)
//bool isBalanced(node *&tree) {
//    if(tree == nullptr)  return true;
//    int lh = height(tree->left);
//    int rh = height(tree->right);
//    if((abs(lh - rh) <= 1 ) && isBalanced(tree->left) && isBalanced(tree->right))  return true;
//    else  return false;
//}

// O(n)
bool isBalanced(node *&tree, int &height) {
    int lh = 0, rh = 0, l = 0, r = 0;
    if(tree == nullptr) {
        height = 0;
        return 1;
    }
    l = isBalanced(tree->left, lh);
    r = isBalanced(tree->right, rh);
    height = max(lh, rh)+1;
    if(abs(lh - rh) >= 2)  return false;
    else  return l && r;
}