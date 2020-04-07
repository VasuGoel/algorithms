#include<bits/stdc++.h>
#define ll long long int
using namespace std;

ll manhattan(pair<ll, ll> a, pair<ll, ll> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll r, c, k, d, x, y;
    cin >> r >> c >> k >> d;
    vector<pair<ll, ll>> dragons;
    for(ll i = 0; i < d; i++)  cin >> x >> y, dragons.push_back(make_pair(x, y));

    ll INF = r*c+1;
    sort(dragons.begin(), dragons.end());
    vector<vector<ll>> cache(d, vector<ll>(d, INF));
    for(ll i = 0; i < d; i++)  cache[0][i] = manhattan(make_pair(0,0), dragons[i]);

    for(int i = 1; i < d; i++) {
        for(int j = 0; j < d; j++) {
            ll minDist = INF;
            for(int k = 0; k < j; k++) {
                minDist = min(minDist, manhattan(dragons[j], dragons[k]) + cache[i-1][k]);
            }
            cache[i][j] = minDist;
        }
    }

    cout << *min_element(cache[k-1].begin(), cache[k-1].end());
    return 0;
}