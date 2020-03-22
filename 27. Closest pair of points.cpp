#include<bits/stdc++.h>
using namespace std;

typedef struct Point {
    int x, y;
} point;

bool compareX(point a, point b) {
    return a.x < b.x;
}

bool compareY(point a, point b) {
    return a.y < b.y;
}

double coord_distance(point a, point b) {
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

double brute_force(vector<point> &points) {
    double min = DBL_MAX;
    for(int i = 0; i < points.size()-1; i++) {
        for(int j = i+1; j < points.size(); j++) {
            if(coord_distance(points[i], points[j]) < min)  min = coord_distance(points[i], points[j]);
        }
    }
    return min;
}

double strip_closest_pair(vector<point> &strip, double d) {
    double min = d;
    sort(strip.begin(), strip.end(), &compareY);
    for(int i = 0; i < strip.size(); i++) {
        for(int j = i+1; j < strip.size()  && (strip[j].y - strip[i].y) < min; j++) {
            if(coord_distance(strip[i], strip[j]) < min)  min = coord_distance(strip[i], strip[j]);
        }
    }
    return min;
}

double closest_pair_util(vector<point> &points, int n) {
    if(n <= 3)  return brute_force(points);
    int mid = n/2;
    point midpoint = points[mid];

    vector<point> points_left = std::vector<point>(points.begin(), points.begin()+mid);
    double dl = closest_pair_util(points_left, mid);
    vector<point> points_right = std::vector<point>(points.begin()+mid, points.end());
    double dr = closest_pair_util(points_right, n-mid);
    double d = min(dl, dr);

    vector<point> strip;
    for(int i = 0; i < n; i++) {
        if(abs(points[i].x - midpoint.x) < d)  strip.push_back(points[i]);
    }
    return min(d, strip_closest_pair(strip, d));
}

double closest_pair(vector<point> &points) {
    sort(points.begin(), points.end(), &compareX);
    return closest_pair_util(points, points.size());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<point> points{{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    cout << "Distance between closest pair of points: " << closest_pair(points);
    return 0;
}