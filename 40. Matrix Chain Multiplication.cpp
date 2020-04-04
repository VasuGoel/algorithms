#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;

void optimalMatrixChainMultiply(vector<int>&rows, vector<int>&cols) {
    vector<vector<ull>> cache(rows.size(), vector<ull>(cols.size(), 0));

    for(int j = 0; j < cols.size(); j++) {
        for(int i = j; i >= 0; i--) {
            if(i < j) {
                cache[i][j] = ULLONG_MAX;
                for(int k = i; k <= j-1; k++) {
                    int subprob = cache[i][k] + cache[k+1][j] + (rows[i]*cols[k]*cols[j]);
                    if(subprob < cache[i][j])  cache[i][j] = subprob;
                }
            }
        }
    }
    cout << "Minimum multiplication steps required: " << cache[0][cols.size()-1] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> rows{4, 2, 3, 1}, cols{2, 3, 1, 3};
    optimalMatrixChainMultiply(rows, cols);
    return 0;
}