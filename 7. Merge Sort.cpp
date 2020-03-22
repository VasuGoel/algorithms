#include<bits/stdc++.h>
using namespace std;

void merge(vector<int> &a, int left, int mid, int right) {
    int *temp = new int[a.size()];
    int i = left, j = mid, k = left;
    while(i <= mid-1 && j <= right) {
        if(a[i] <= a[j])  temp[k++] = a[i++];
        else  temp[k++] = a[j++];
    }
    while(i <= mid-1)  temp[k++] = a[i++];
    while(j <= right)  temp[k++] = a[j++];
    for(int i = left; i <= right; i++)  a[i] = temp[i];
}

void mergeSort(vector<int> &a, int left, int right) {
    if(left < right) {
        int mid = (left+right)/2;
        mergeSort(a, left, mid);
        mergeSort(a, mid+1, right);
        merge(a, left, mid+1, right);
    }
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
    mergeSort(a, 0, a.size()-1);
    cout << "After sorting: ";
    for(int val : a)  cout << val << " ";
    return 0;
}