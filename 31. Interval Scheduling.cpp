#include<bits/stdc++.h>
using namespace std;

typedef struct Interval {
    int start, finish;
} interval;

bool comparator(interval i, interval j) {
    return i.finish < j.finish;
}

vector<interval> interval_scheduler(vector<interval> &slots) {
    vector<interval> picked_intervals;
    sort(slots.begin(), slots.end(), &comparator);
    picked_intervals.push_back(slots[0]);
    interval picked = picked_intervals[0];
    for(int i = 1; i < slots.size(); i++) {
        if(slots[i].start > picked.finish)  picked_intervals.push_back(slots[i]), picked = slots[i];
    }
    return picked_intervals;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int s, f;
    vector<interval> slots{{0,25}, {29, 33}, {0, 5},
                           {8, 15}, {18, 23}, {28, 34},
                           {0, 11}, {13, 19}, {21, 26}};
    vector<interval> picked_intervals = interval_scheduler(slots);
    cout << "Out of given " << slots.size() << " intervals, following " << picked_intervals.size() << " intervals were scheduled: \n";
    for(interval i: picked_intervals) {
        cout << i.start << " " << i.finish << "\n";
    }
    return 0;
}