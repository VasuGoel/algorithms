#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;

ull memoizedGridPath(int x, int y, vector<pair<int, int>> &holes) {
    ull pairs;
    static map<pair<int, int>, ull> cache;
    auto found = cache.find(pair<int, int>(x, y));
    if(found != cache.end())  return cache[pair<int, int>(x, y)];

    auto itr = find(holes.begin(), holes.end(), make_pair(x, y));
    if(itr != holes.end())  return 0;
    if(x == 0 && y == 0)  return 1;
    else if(x == 0)  pairs = memoizedGridPath(0, y-1, holes);
    else if(y == 0)  pairs = memoizedGridPath(x-1, 0, holes);
    else  pairs = memoizedGridPath(x-1, y, holes) + memoizedGridPath(x, y-1, holes);
    cache.insert({make_pair(x,y), pairs});
    return pairs;
}

ull dynamicGridPath(int x, int y, vector<pair<int, int>> &holes) {
    vector<vector<ull>> cache(y+1, vector<ull>(x+1, 1));
    for(pair<int, int> h: holes)  cache[y-h.second][h.first] = 0;

    for(int i = y; i >= 0; i--) {
        for(int j = 0; j <= x; j++) {
            if(cache[i][j] != 0) {
                if (i == y || j == 0) cache[i][j] = 1;
                else cache[i][j] = cache[i][j-1] + cache[i+1][j];
            }
        }
    }
    return cache[0][x];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int x, y, h, p, q;
    vector<pair<int, int>> holes;
    cout << "Enter destination coordinates: ";
    cin >> x >> y;
    cout << "Enter number of holes in grid: ";
    cin >> h;
    if(h != 0) {
        cout << "Enter " << h << " hole coordinates: \n";
        while(h--) {
            cin >> p >> q;
            holes.push_back(make_pair(p, q));
        }
    }

    cout << "\nGrid, where S = (0,0) and F = (" << x << "," << y << ") and H holes.\n";
    vector<vector<char>> grid(y+1, vector<char>(x+1, '.'));
    grid[y][0] = 'S', grid[0][x] = 'F';
    for(pair<int, int> h: holes)  grid[y-h.second][h.first] = 'H';
    for(vector<char> g: grid) {
        for(char c: g)  cout << c << "\t";
        cout << "\n";
    }

    cout << "\nGiven you can only move up or right, total number of paths from S to F:\n";
    cout << "memoizedGridPaths(" << x << "," << y << "): " << memoizedGridPath(x,y, holes) << "\n";
    cout << "dynamicGridPaths(" << x << "," << y << "): " << dynamicGridPath(x,y, holes) << "\n";
    return 0;
}