#include<bits/stdc++.h>
using namespace std;

typedef struct Node {
    int data;
    Node *parent, *left, *right;
} node;

bool check_duplicates(vector<int> v) {
    sort(v.begin(), v.end());
    int count = std::distance(v.begin(), std::unique(v.begin(), v.begin() + v.size()));
    return count == v.size();
}

node *tree = nullptr;
void create_binary_tree(node *&, vector<int> &);
void insert(node *&, int);
bool search(node *&, int);
void delete_element(node *&, int);
void display_tree(node *&);
void preorder_traversal(node *&);
void inorder_traversal(node *&);
void postorder_traversal(node *&);
node *min_element(node *&);
node *max_element(node *&);
node *predecessor(node *&, int);
node *successor(node *&, int);
int count_total_nodes(node *&);
int count_internal_nodes(node *&);
int count_external_nodes(node *&);
int height(node *&);
node *clone_tree(node *&, node *&);
void mirror_image(node *&);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int choice, val;
    vector<int> values;
    cout << "\n1. create_binary_tree()\t\t\t2. insert()\n3. search()\t\t\t\t\t\t4. delete()\n5. display_tree()"
         << "\t\t\t\t6. preorder_traversal()\n7. inorder_traversal()\t\t\t8. postorder_traveral()\n9. min_element()\t\t\t\t10. max_element()\n"
         << "11. predecessor()\t\t\t\t12. successor()\n13. delete_tree()\t\t\t\t14. count_total_nodes()\n15. count_internal_nodes()\t\t16. count_external_nodes()\n"
         << "17. height()\t\t\t\t\t18. mirror_image()\n19. EXIT\n";
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
                    create_binary_tree(tree, values);
                    cout << "Binary Search Tree created.\n";
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

            case 6: if(tree != nullptr) {
                    cout << "Pre-order traversal: ";
                    preorder_traversal(tree); cout << "\n";
                } else  cout << "Tree empty.\n";
                break;

            case 7: if(tree != nullptr) {
                    cout << "In-order traversal: ";
                    inorder_traversal(tree); cout << "\n";
                } else  cout << "Tree empty.\n";
                break;

            case 8: if(tree != nullptr) {
                    cout << "Post-order traversal: ";
                    postorder_traversal(tree); cout << "\n";
                } else  cout << "Tree empty.\n";
                break;

            case 9: if(tree != nullptr)  cout << "Minimum element: " << min_element(tree)->data << "\n";
                else  cout << "Tree empty.\n";
                break;

            case 10:if(tree != nullptr)  cout << "Maximum element: " << max_element(tree)->data << "\n";
                else  cout << "Tree empty.\n";
                break;

            case 11:cout << "Enter value to find predecessor of: ";
                cin >> val;
                if(search(tree, val))  {
                    node *pred = predecessor(tree, val);
                    if(pred != nullptr)  cout << "Predecessor of " << val << " : " << pred->data << "\n";
                    else  cout << val << " has no predecessor.\n";
                }
                else  cout << val << " not found in tree.\n";
                break;

            case 12:cout << "Enter value to find successor of: ";
                cin >> val;
                if(search(tree, val))  {
                    node *succ = successor(tree, val);
                    if(succ != nullptr)  cout << "Successor of " << val << " : " << succ->data << "\n";
                    else  cout << val << " has no successor.\n";
                }
                else  cout << val << " not found in tree.\n";
                break;

            case 13:tree = nullptr;
                cout << "Tree deleted.\n";
                break;

            case 14:cout << "Total nodes: " << count_total_nodes(tree) << "\n";
                break;

            case 15:cout << "Internal nodes: " << count_internal_nodes(tree) << "\n";
                break;

            case 16:cout << "External nodes: " << count_external_nodes(tree) << "\n";
                break;

            case 17:if(tree == nullptr)  cout << "Tree empty.\n";
                else  cout << "Height of tree: " << height(tree) << "\n";
                break;

            case 18:if(tree == nullptr)  cout << "Tree empty.\n";
                else {
                    node *copy = clone_tree(copy, tree);
                    mirror_image(copy);
                    cout << "Mirror image of tree: \n";
                    display_tree(copy);
                }
                break;

            case 19:break;

            default:cout << "Not a valid choice.\n";
                break;
        }
    } while(choice != 19);
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

bool search(node *&tree, int val) {
    if(tree == nullptr)  return false;
    if(tree->data == val)  return true;
    else if(val < tree->data)  return search(tree->left, val);
    else  return search(tree->right, val);
}

void delete_element(node *&tree, int val) {
    if(tree == nullptr) {
        cout << val << " not found in tree.\n"; return;
    }
    if(val < tree->data) {
        delete_element(tree->left, val); return;
    }
    else if(val > tree->data) {
        delete_element(tree->right, val); return;
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

void preorder_traversal(node *&tree) {
    if(tree != nullptr) {
        cout << tree->data << " ";
        preorder_traversal(tree->left);
        preorder_traversal(tree->right);
    }
}

void inorder_traversal(node *&tree) {
    if(tree != nullptr) {
        inorder_traversal(tree->left);
        cout << tree->data << " ";
        inorder_traversal(tree->right);
    }
}

void postorder_traversal(node *&tree) {
    if(tree != nullptr) {
        postorder_traversal(tree->left);
        postorder_traversal(tree->right);
        cout << tree->data << " ";
    }
}

node *min_element(node *&tree) {
    if(tree == nullptr || tree->left == nullptr)  return tree;
    else  return min_element(tree->left);
}

node *max_element(node *&tree) {
    if(tree == nullptr || tree->right == nullptr)  return tree;
    else  return max_element(tree->right);
}

node *predecessor(node *&tree, int val) {
    node *ptr = tree;
    while(ptr->data != val) {
        if(val < ptr->data)  ptr = ptr->left;
        else  ptr = ptr->right;
    }

    if(ptr->left != nullptr)  return max_element(ptr->left);
    else {
        node *preptr = ptr->parent;
        while(preptr != nullptr && ptr == preptr->left) {
            ptr = preptr;
            preptr = ptr->parent;
        }
        return preptr;
    }
}

node *successor(node *&tree, int val) {
    node *ptr = tree;
    while(ptr->data != val) {
        if(val < ptr->data)  ptr = ptr->left;
        else  ptr = ptr->right;
    }

    if(ptr->right != nullptr)  return min_element(ptr->right);
    else {
        node *preptr = ptr->parent;
        while(preptr != nullptr && ptr == preptr->right) {
            ptr = preptr;
            preptr = ptr->parent;
        }
        return preptr;
    }
}

int count_total_nodes(node *&tree) {
    if(tree == nullptr)  return 0;
    else  return count_total_nodes(tree->left) + count_total_nodes(tree->right) + 1;
}

int count_internal_nodes(node *&tree) {
    if(tree == nullptr)  return 0;
    if(tree->left == nullptr && tree->right == nullptr)  return 0;
    else  return count_internal_nodes(tree->left) + count_internal_nodes(tree->right) + 1;
}

int count_external_nodes(node *&tree) {
    if(tree == nullptr)  return 0;
    if(tree->left == nullptr && tree->right == nullptr)  return 1;
    else  return count_external_nodes(tree->left) + count_external_nodes(tree->right);
}

int height(node *&tree) {
    if(tree == nullptr)  return 0;
    else {
        int leftHeight = height(tree->left);
        int rightHeight = height(tree->right);
        if(leftHeight > rightHeight)  return leftHeight+1;
        else  return rightHeight+1;
    }
}

node *clone_tree(node *&cloned, node *&oldTree) {
    vector<int> values;
    queue<node *> q;
    q.push(oldTree);
    while(!q.empty()) {
        int level_node_count = q.size();
        while(level_node_count--) {
            node *node = q.front();
            values.push_back(node->data);
            q.pop();
            if(node->left != nullptr)  q.push(node->left);
            if(node->right != nullptr) q.push(node->right);
        }
    }
    create_binary_tree(cloned, values);
    return cloned;
}

void mirror_image(node *&tree) {
    if(tree == nullptr)  return;
    else {
        mirror_image(tree->left);
        mirror_image(tree->right);
        node *temp = tree->left;
        tree->left = tree->right;
        tree->right = temp;
    }
}
