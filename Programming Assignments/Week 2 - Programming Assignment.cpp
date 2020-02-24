#include<bits/stdc++.h>
using namespace std;

typedef struct Interval {
    int s, e;
    Interval(long s, long e) {
        this->s = s, this->e = e;
    }
} interval;

bool comparator(interval a, interval b) {
    return a.s < b.s || (a.s == b.s && a.e <= b.e);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long c, n, k, s, e, i;
    cin >> c >> n >> k;
    vector<interval> intervals;
    for(i = 0; i < n; i++)  cin >> s >> e, intervals.push_back(interval(s, e));
    sort(intervals.begin(), intervals.end(), &comparator);

    long overlaps = 0, overlap_length = 0;
    for(i = 0; i < intervals.size()-1; i++) {
        if(intervals[i+1].s <= intervals[i].e) {
            if(intervals[i+1].s == intervals[i].s)  overlap_length = intervals[i].e - intervals[i].s + 1;
            else if(intervals[i+1].s > intervals[i].s && intervals[i+1].e <= intervals[i].e)  overlap_length = intervals[i+1].e - intervals[i+1].s + 1;
            else if(intervals[i+1].s > intervals[i].s && intervals[i+1].e > intervals[i].e)  overlap_length = intervals[i].e - intervals[i+1].s + 1;
            overlaps++;
            if (overlaps > 1) break;
        }
    }

    if(k == 0) {
        if(overlaps > 1 || overlap_length > 0)  cout << "Bad\n";
        else  cout << "Good\n";
    } else if(k == 1) {
        if(overlaps > 1)  cout << "Bad\n";
        else {
            if(intervals[0].s - 1 >= overlap_length || c - intervals[intervals.size()-1].e >= overlap_length)  cout << "Good\n";
            else {
                for(i = 1; i < intervals.size(); i++) {
                    if(intervals[i].s - intervals[i-1].e - 1 >= overlap_length)  break;
                }
                if(i == intervals.size())  cout << "Bad\n";
                else  cout << "Good\n";
            }
        }
    }
    return 0;
}