#include <bits/stdc++.h>
using namespace std;

int linear_search(int values[], int n, int key) {
    for(int i = 0; i < n; i++)  if(values[i] == key)  return i;
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, key, index;
    cin >> n;
    int values[n];
    for(int i = 0; i < n; i++)  cin >> values[i];
    cin >> key;
    index = linear_search(values, n, key);
    if(index != -1)  cout << "Element found at index: " << index << '\n';
    else  cout << "Element not found in the array.\n";
    return 0;
}

