#include<bits/stdc++.h>
using namespace std;

typedef struct Node {
    int data;
    Node *parent, *left, *right;
    int height = 1;
} node;

bool check_duplicates(vector<int> v) {
    sort(v.begin(), v.end());
    int count = std::distance(v.begin(), std::unique(v.begin(), v.begin() + v.size()));
    return count == v.size();
}

node *tree = nullptr;
void create_avl_tree(node *&, vector<int> &);
void insert(node *&, int);
bool search(node *&, int);
void delete_element(node *&, int);
void display_tree(node *&);
void rotateRight(node *&);
void rotateLeft(node *&);
void rebalance(node *&);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int choice, val;
    vector<int> values;
    cout << "\n1. create_avl_tree()\t\t\t2. insert()\n3. search()\t\t\t\t\t\t4. delete()\n5. display_tree()"
         << "\t\t\t\t6. EXIT\n";
    cout << "---------------------------------------------\n";

    do{
        cout << "\nEnter choice: ";
        cin >> choice;
        switch(choice) {
            case 1: cout << "Enter values into binary search tree (no duplicates). Enter -1 to stop: ";
                cin >> val;
                while(val != -1) {
                    values.push_back(val);
                    cin >> val;
                }
                tree = nullptr;
                if(check_duplicates(values)) {
                    create_avl_tree(tree, values);
                    cout << "AVl tree created.\n";
                } else  cout << "No duplicates allowed.\n";
                values.clear();
                break;

            case 2: cout << "Enter value to insert: ";
                cin >> val;
                if(!search(tree, val))  insert(tree, val), cout << val << " inserted in tree.\n";
                else  cout << val << " already present in tree.\n";
                break;

            case 3: cout << "Enter value to search: ";
                cin >> val;
                if(search(tree, val))  cout << val << " found in tree.\n";
                else  cout << val << " not found in tree.\n";
                break;

            case 4: cout << "Enter value to delete from tree: ";
                cin >> val;
                if(search(tree, val))  delete_element(tree, val), cout << val << " deleted from tree.\n";
                break;

            case 5: if(tree == nullptr)  cout << "Tree empty.\n";
                else  cout << "Tree: \n", display_tree(tree);
                break;

            case 6: break;

            default:cout << "Not a valid choice.\n";
                break;
        }
    } while(choice != 6);

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

bool search(node *&tree, int val) {
    if(tree == nullptr)  return false;
    if(tree->data == val)  return true;
    else if(val < tree->data)  return search(tree->left, val);
    else  return search(tree->right, val);
}

node *max_element(node *&tree) {
    if(tree == nullptr || tree->right == nullptr)  return tree;
    else  return max_element(tree->right);
}

void delete_element(node *&tree, int val) {
    if(tree == nullptr) {
        cout << val << " not found in tree.\n"; return;
    }
    if(val < tree->data) {
        delete_element(tree->left, val), rebalance(tree); return;
    }
    else if(val > tree->data) {
        delete_element(tree->right, val), rebalance(tree); return;
    }

    // case 1: delete root and leaves
    if(tree->parent == nullptr && tree->left == nullptr && tree->right == nullptr) {
        tree = nullptr;
        return;

    }
    if(tree->left == nullptr && tree->right == nullptr) {
        if(tree == tree->parent->left)  tree->parent->left = nullptr;
        else if(tree == tree->parent->right)  tree->parent->right = nullptr;
        return;
    }

    // case 2: delete node with one child (left or right)
    if(tree->left != nullptr && tree->right == nullptr) {
        tree->left->parent = tree->parent;
        if(tree == tree->parent->left)  tree->parent->left = tree->left;
        else if(tree == tree->parent->right)  tree->parent->right = tree->left;
        return;
    } else if(tree->right != nullptr && tree->left == nullptr) {
        tree->right->parent = tree->parent;
        if(tree == tree->parent->left)  tree->parent->left = tree->right;
        else if(tree == tree->parent->right)  tree->parent->right = tree->right;
        return;
    }

    // case 3: delete node with two children
    if(tree->left != nullptr && tree->right != nullptr) {
        node *pred = max_element(tree->left);
        tree->data = pred->data;
        delete_element(tree->left, pred->data);
        rebalance(tree);
        return;
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