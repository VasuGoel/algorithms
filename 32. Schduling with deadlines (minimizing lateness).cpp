#include<bits/stdc++.h>
using namespace std;

typedef struct Request {
    int time_taken, deadline;
} request;

bool comparator(request i, request j) {
    return i.deadline < j.deadline || (i.deadline == j.deadline && i.time_taken < j.time_taken);
}

void schedule_with_deadlines(vector<request> &requests) {
    sort(requests.begin(), requests.end(), &comparator);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<request> requests{{1, 100}, {10, 10}};
    schedule_with_deadlines(requests);
    cout << "Requests after scheduling with deadlines: \n";
    int start = 0, finish = 0, lateness = 0;
    for(request req: requests) {
        cout << req.time_taken << " " << req.deadline << "\n";
        finish = (start+req.time_taken);
        if(finish > req.deadline)  lateness += (finish-req.deadline);
        start = finish;
    }
    cout << "Maximum lateness over all requests is minimized and is: " << lateness << "\n";
    return 0;
}
