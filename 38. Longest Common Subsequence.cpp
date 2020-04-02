#include<bits/stdc++.h>
using namespace std;

// O(mn) dynamic programming
void longestCommonSubsequence(string m, string n) {
    vector<vector<int>> cache(m.size()+1, vector<int>(n.size()+1, 0));
    for(int j = n.size(); j >= 0; j--) {
        for(int i = m.size(); i >= 0; i--) {
            if(i == m.size() || j == n.size())  cache[i][j] = 0;
            else if(n[j] != m[i])  cache[i][j] = max(cache[i+1][j], cache[i][j+1]);
            else if(n[j] == m[i])  cache[i][j] = 1 + cache[i+1][j+1];
        }
    }

    string lcs;
    int i = 0, j = 0, max = cache[0][0];
    while(i <= m.size() && j <= n.size()) {
        if(cache[i][j] == cache[i][j+1])  j = j+1;
        else if(cache[i][j] == cache[i+1][j])  i = i+1;
        else {
            lcs += n[j], i = i+1, j = j+1, max--;
        }
        if(max == 0)  break;
    }
    cout << "longestCommonSubsequence(" << m << "," << n << "): " << lcs << "(len: " << lcs.size() << ")\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string m, n;
    cout << "Enter 2 strings: ";
    cin >> m >> n;
    longestCommonSubsequence(m,n);
    return 0;
}