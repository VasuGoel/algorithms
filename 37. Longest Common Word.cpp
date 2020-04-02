#include<bits/stdc++.h>
using namespace std;

// O(mn^2) brute force
void bruteLongestCommonWord(string m, string n) {
    int s, e;
    string word, lcw;
    for(int i = 0; i < m.size(); i++) {
        for(int j = 0; j < n.size(); j++) {
            if(m[i] == n[j]) {
                s = i, e = j, word = "";
                while(s < m.size() && e < n.size() && m[s] == n[e])  word += m[s], s++, e++;
                if(word.size() > lcw.size())  lcw = word;
            }
        }
    }
    cout << "\nbruteLongestCommonWord(" << m << "," << n << "): " << lcw << " (len: " << lcw.size() << ")\n";
}

// O(mn) dynamic programming
void dynamicLongestCommonWord(string m, string n) {
    vector<vector<int>> cache(m.size()+1, vector<int>(n.size()+1, 0));
    int max = 0, u, v;
    for(int j = n.size(); j >= 0; j--) {
        for(int i = 0; i <= m.size(); i++) {
            if(i == m.size() || j == n.size())  cache[i][j] = 0;
            else if(n[j] != m[i])  cache[i][j] = 0;
            else if(n[j] == m[i])  cache[i][j] = 1 + cache[i+1][j+1];
            if(cache[i][j] > max)  max = cache[i][j], u = i, v = j;
        }
    }
    string lcw;
    while(max--)  lcw += n[v], v++;
    cout << "\ndynamicLongestCommonWord(" << m << "," << n << "): " << lcw << " (len: " << lcw.size() << ")\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string m, n;
    cout << "Enter 2 strings: ";
    cin >> m >> n;
    bruteLongestCommonWord(m, n);
    dynamicLongestCommonWord(m, n);
    return 0;
}