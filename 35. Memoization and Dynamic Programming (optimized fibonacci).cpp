#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;

ull iterativeFibonacci(int n) {
    ull prev = 0, curr = 1, next;
    if(n == 0 || n == 1)  return n;
    for(int i = 2; i <= n; i++) {
        next = prev + curr;
        prev = curr;
        curr = next;
    }
    return next;
}

ull memoizedFibonacci(int n) {
    static map<int, ull> cache{{0,0}, {1, 1}};
    auto found = cache.find(n);
    if(found != cache.end())  return found->second;
    ull result = memoizedFibonacci(n-1) + memoizedFibonacci(n-2);
    cache.insert(pair<int, ull>(n, result));
    return result;
}

ull dynamicFibonacci(int n) {
    vector<ull> fibTable{0,1};;
    for(int i = 2; i <= n; i++)  fibTable.push_back(fibTable[i-1] + fibTable[i-2]);
    return fibTable[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "iterativeFibonacci(" << n << "): " << iterativeFibonacci(n) << "\n";
    cout << "memoizedFibonacci(" << n << "): " << memoizedFibonacci(n) << "\n";
    cout << "dynamicFibonacci(" << n << "): " << dynamicFibonacci(n) << "\n";
    return 0;
}