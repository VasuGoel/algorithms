#include <bits/stdc++.h>
using namespace std;

void insertion_sort(int values[], int n) {
    for(int i = 1; i < n; i++) {
        int j = i;
        while(j > 0 && values[j] < values[j-1]) {
            int temp = values[j];
            values[j] = values[j-1];
            values[j-1] = temp;
            j--;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int values[n];
    for(int i = 0; i < n; i++)  cin >> values[i];
    insertion_sort(values, n);
    for(int i = 0; i < n; i++)  cout << values[i] << ' ';
    return 0;
}