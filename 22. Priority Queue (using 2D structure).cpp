#include<bits/stdc++.h>
#define n 25
using namespace std;

int delete_max(vector<int> priority_queue[(int)sqrt(n)]) {
    int r = 0;
    int max = priority_queue[0][priority_queue[0].size()-1];
    for(int i = 1; i < (int)sqrt(n); i++) {
        if(priority_queue[i][priority_queue[i].size()-1] > max) {
            max = priority_queue[i][priority_queue[i].size()-1];
            r = i;
        }
    }
    priority_queue[r].pop_back();
    return max;
}

void insert(int num, vector<int> priority_queue[(int)sqrt(n)]) {
    int i;
    for(i = 0; i < sqrt(n); i++) {
        if(priority_queue[i].size() != sqrt(n)) {
            priority_queue[i].push_back(num);
            sort(priority_queue[i].begin(), priority_queue[i].end());
            break;
        }
    }
    if(i == sqrt(n))  cout << "Priority queue full.\n";
    else  cout << num << " inserted into the priority queue.\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int choice;
    vector<int> priority_queue[(int)sqrt(n)];

    int r1[] = {12, 17, 29, 31, 40};
    int r2[] = {8, 19, 22, 33, 40};
    int r3[] = {10, 13, 14};
    int r4[] = {13, 20, 25, 43};
    int r5[] = {6, 11};
    priority_queue[0].insert(priority_queue[0].end(), std::begin(r1), std::end(r1));
    priority_queue[1].insert(priority_queue[1].end(), std::begin(r2), std::end(r2));
    priority_queue[2].insert(priority_queue[2].end(), std::begin(r3), std::end(r3));
    priority_queue[3].insert(priority_queue[3].end(), std::begin(r4), std::end(r4));
    priority_queue[4].insert(priority_queue[4].end(), std::begin(r5), std::end(r5));

    cout << "\n1. delete_max()\t\t\t\t\t\t2. insert\n3. display_priority_queue_2D()\t\t4. EXIT\n";
    cout << "----------------------------------------------------------------------\n";
    cout << "\nEnter your choice: ";
    cin >> choice;
    while(choice != 4) {
        switch(choice) {
            case 1: cout << delete_max(priority_queue) << " deleted from priority queue.\n";
                break;
            case 2: int num;
                cout << "Enter number: ";
                cin >> num;
                insert(num, priority_queue);
                break;
            case 3: for(int i = 0; i < sqrt(n); i++) {
                    for(int j : priority_queue[i])  cout << j << " ";
                    cout << endl;
                }
                break;
            case 4: return 0;
            default: cout << "Wrong choice!\n";
        }
        cout << "\nEnter your choice: ";
        cin >> choice;
    }
    return 0;
}