#include <bits/stdc++.h>
using namespace std;

void selection_sort(int values[], int n) {
    for(int i = 0; i < n-1; i++) {
        int min = values[i], pos = i;
        for(int j = i; j < n; j++) {
            if (values[j] < min) min = values[j], pos = j;
        }
        int temp = values[i];
        values[i] = values[pos];
        values[pos] = temp;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int values[n];
    for(int i = 0; i < n; i++)  cin >> values[i];
    selection_sort(values, n);
    for(int i = 0; i < n; i++)  cout << values[i] << ' ';
    return 0;
}