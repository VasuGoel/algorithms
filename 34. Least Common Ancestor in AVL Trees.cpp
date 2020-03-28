#include<bits/stdc++.h>
using namespace std;

typedef struct Node {
    int data;
    Node *parent, *left, *right;
    int height = 1;
} node;

node *tree = nullptr;
void create_avl_tree(node *&, vector<int> &);
void insert(node *&, int);
void rotateRight(node *&);
void rotateLeft(node *&);
void rebalance(node *&);
void display_tree(node *&);
int least_common_ancestor(node *&, int, int);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> values{74, 34, 244, 14, 48, 100, 1111, 12, 20, 35, 58, 98, 200, 436, 67567, 2, 234, 324, 948, 2323, 564657};
    create_avl_tree(tree, values);
    cout << "AVL tree:\n";
    display_tree(tree);

    int v1, v2;
    cout << "\nEnter value of nodes of which to find lowest common ancestor of: ";
    cin >> v1 >> v2;
    int lca = least_common_ancestor(tree, v1, v2);
    if(lca != -1)  cout << "Least common ancestor of " << v1 << " and " << v2 << ": " << lca << "\n";
    else  cout << "Invalid pair of nodes.\n";
    return 0;
}

void create_avl_tree(node *&tree, vector<int> &values) {
    for(int val: values)  insert(tree, val);
}

void update_height_up(node *&tree) {
    if(tree->parent != nullptr) {
        tree->parent->height = max(tree->parent->height, tree->height+1);
        update_height_up(tree->parent);
    }
}

void insert(node *&tree, int val) {
    node *new_node;
    new_node = new node;
    new_node->data =  val, new_node->left = nullptr, new_node->right = nullptr;

    if(tree == nullptr) {
        tree = new_node;
        tree->parent = nullptr, tree->left = nullptr, tree->right = nullptr, tree->height = 1;
        return;
    }
    if(val == tree->data) {
        cout << val << " already present in tree.\n";
        return;
    }
    else {
        if(val < tree->data) {
            if(tree->left == nullptr)  tree->left = new_node, new_node->parent = tree, update_height_up(tree->left);
            else  insert(tree->left, val), rebalance(tree);
        } else {
            if(tree->right == nullptr)  tree->right = new_node, new_node->parent = tree, update_height_up(tree->right);
            else  insert(tree->right, val), rebalance(tree);
        }
    }
}

void rotateRight(node *&tree) {
    int x = tree->data;
    int y = tree->left->data;
    node *tll = tree->left->left;
    node *tlr = tree->left->right;
    node *tr = tree->right;

    tree->data = y;
    tree->right = tree->left;
    tree->right->data = x;
    tree->left = tll;
    tree->right->left = tlr;
    tree->right->right = tr;
    if(tll != nullptr)  tll->parent = tree;
    if(tlr != nullptr)  tlr->parent = tree->right;
    if(tr != nullptr)  tr->parent = tree->right;
}

void rotateLeft(node *&tree) {
    int y = tree->data;
    int z = tree->right->data;
    node *tll = tree->left;
    node *tlrl = tree->right->left;
    node *tlrr = tree->right->right;

    tree->data = z;
    tree->left = tree->right;
    tree->left->data = y;
    tree->left->left = tll;
    tree->left->right = tlrl;
    tree->right = tlrr;
    if(tll != nullptr)  tll->parent = tree->left;
    if(tlrl != nullptr)  tlrl->parent = tree->left;
    if(tlrr != nullptr)  tlrr->parent = tree;
}

int slope(node *tree) {
    if(tree->left != nullptr && tree->right != nullptr)  return tree->left->height - tree->right->height;
    else if(tree->left != nullptr && tree->right == nullptr)  return tree->left->height;
    else  return -(tree->right->height);
}

void rebalance_update_height(node *tree) {
    if(tree->parent != nullptr) {
        if(tree->parent->left != nullptr && tree->parent->right != nullptr)
            tree->parent->height = max(tree->parent->left->height+1, tree->parent->right->height+1);
        else if(tree->parent->left != nullptr && tree->parent->right == nullptr)
            tree->parent->height = tree->parent->left->height+1;
        else  tree->parent->height = tree->parent->right->height+1;
        rebalance_update_height(tree->parent);
    }
}

void rebalance(node *&tree) {
    if(slope(tree) == 2) {
        if(slope(tree->left) == -1)  rotateLeft(tree->left);
        rotateRight(tree);
        tree->height--;
        tree->right->height--;

        rebalance_update_height(tree);
        cout << "Tree rebalanced.\n";
    }
    if(slope(tree) == -2) {
        if(slope(tree->right) == 1)  rotateRight(tree->right);
        rotateLeft(tree);
        tree->height--;
        tree->left->height--;

        rebalance_update_height(tree);
        cout << "Tree rebalanced.\n";
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

void find_path(node *tree, int v, vector<int> &path) {
    if(tree == nullptr) {
        path.clear();
        return;
    }
    else {
        path.push_back(tree->data);
        if(v == tree->data)  return;
        if(v < tree->data)  find_path(tree->left, v, path);
        if(v > tree->data)  find_path(tree->right, v, path);
    }
}

int least_common_ancestor(node *&tree, int v1, int v2) {
    vector<int> path_v1, path_v2;
    find_path(tree, v1, path_v1);
    find_path(tree, v2, path_v2);

    if(path_v1.empty() || path_v2.empty())  return -1;
    for(int i = max(path_v1.size(), path_v2.size())-1; i >= 0; i--) {
        if(path_v1[i] == path_v2[i]) {
            return path_v1[i];
        }
    }
}