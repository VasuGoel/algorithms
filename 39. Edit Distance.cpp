#include<bits/stdc++.h>
using namespace std;

int min(int a, int b, int c) {
    if(a < b && a < c)  return a;
    if(b < a && b < c)  return b;
    return c;
}

// O(mn) dynamic programming with space complexity O(mn)
void editDistance(string m, string n) {
    vector<vector<int>> cache(m.size()+1, vector<int>(n.size()+1, 0));
    for(int j = n.size(); j >= 0; j--) {
        for(int i = m.size(); i >= 0; i--) {
            if(i == m.size() && j == n.size())  cache[i][j] = 0;
            else if(i == m.size())  cache[i][j] = n.size()-j;
            else if(j == n.size())  cache[i][j] = m.size()-i;
            else if(n[j] == m[i])  cache[i][j] = cache[i+1][j+1];
            else if(n[j] != m[i])  cache[i][j] = 1 + min(cache[i][j+1], cache[i+1][j+1], cache[i+1][j]);
        }
    }

    int i = 0, j = 0, min = cache[0][0], ins = 0, del = 0, subs = 0;
    while(i <= m.size() && j <= n.size() && min > 0) {
        // corner condition
        if(i+1 > m.size()) ins++, min--;
        else if(j+1 > n.size())  del++, min--;

        else if(cache[i][j] == 1 + cache[i+1][j])  i = i+1, del++, min--;
        else if(cache[i][j] == 1 + cache[i][j+1])  j = j+1, ins++, min--;
        else if(cache[i][j] == 1 + cache[i+1][j+1])  i = i+1, j = j+1, subs++, min--;
        else if(cache[i][j] == cache[i+1][j+1])  i = i+1, j = j+1;
    }
    cout << "On character-level:\nTotal changes: " << ins+del+subs << ",\tinsertions: " << ins << ",\tdeletions: " << del << ",\tsubstitutions: " << subs << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string m, n;
    cout << "Enter 2 sentences -\n";
    cout << "old: "; getline(cin, m);
    cout << "new: "; getline(cin, n);
    editDistance(m, n);
    return 0;
}