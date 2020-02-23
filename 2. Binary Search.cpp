#include <bits/stdc++.h>
using namespace std;

int binary_search(int values[], int n, int key, int begin, int end) {
    if(begin > end)  return -1;
    int mid = (begin+end)/2;
    if(values[mid] == key)
        return mid;
    else if(key < values[mid])
        return binary_search(values, n, key, begin, mid-1);
    else
        return binary_search(values, n, key, mid+1, end);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, key;
    cin >> n;
    int values[n];
    for(int i = 0; i < n; i++)  cin >> values[i];
    cin >> key;
    int index = binary_search(values, n, key, 0, n-1);
    if(index != -1)  cout << "Element found in the array at index: " << index << "\n";
    else  cout << "Element not found in the array.\n";
    return 0;
}