#include<bits/stdc++.h>
using namespace std;

int mergeCount(vector<int> &a, int left, int mid, int right) {
    int *temp = new int[a.size()];
    int i = left, j = mid, k = left, count = 0;
    while(i <= mid-1 && j <= right) {
        if(a[i] <= a[j])  temp[k++] = a[i++];
        else {
            temp[k++] = a[j++];
            count += mid-i;
        }
    }
    while (i <= mid - 1)  temp[k++] = a[i++];
    while (j <= right)  temp[k++] = a[j++];
    for (i = left; i <= right; i++)  a[i] = temp[i];
    return count;
}

int mergeSortCount(vector<int> &a, int left, int right) {
    int count = 0;
    if(right > left) {
        int mid = (left+right)/2;
        count += mergeSortCount(a, left, mid);
        count += mergeSortCount(a, mid+1, right);
        count += mergeCount(a, left, mid+1, right);
    }
    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int val;
    vector<int> a;
    cout << "Enter values in vector (and -1 to stop): ";
    cin >> val;
    while(val != -1) {
        a.push_back(val);
        cin >> val;
    }
    cout << "Number of inversions: " << mergeSortCount(a, 0, a.size()-1);
    cout << "\nAfter sorting: ";
    for(int val : a)  cout << val << " ";
    return 0;
}