#include <bits/stdc++.h>
using namespace std;

void bubble_sort(int values[], int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(values[j] > values[j+1]) {
                int temp = values[j+1];
                values[j+1] = values[j];
                values[j] = temp;
            }
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
    bubble_sort(values, n);
    for(int i = 0; i < n; i++)  cout << values[i] << ' ';
    return 0;
}