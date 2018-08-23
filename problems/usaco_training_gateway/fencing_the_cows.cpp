/*
ID: andreip3
LANG: C++14
TASK: fc
*/
#include <bits/stdc++.h>

using namespace std;

struct Point {
    double x, y;
}v[120005];

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double ccp(Point a, Point b, Point c) {
    return (a.x-b.x)*(c.y-b.y)-(a.y-b.y)*(c.x-b.x);
}

Point center;
bool operator<(const Point &a,const Point &b) {
    return (ccp(a,center,b)>0);
}

int main() {
    ifstream cin("fc.in");
    ofstream cout("fc.out");
    center.x = center.y = 1000000005;
    
	int n = 0, i, unde;
    cin >> n;
    for (i = 0; i < n; i++) {
        cin >> v[i].x >> v[i].y;
        if(v[i].x < center.x)
            center = v[i],unde = i;
        else if (v[i].x == center.x)
            if (v[i].y < center.y)
                center = v[i],unde = i;
    }
    swap(v[0], v[unde]);
    sort(v+1, v+n);

    Point stk[12005];
    int pos = -1;
    stk[++pos] = v[0];
    stk[++pos] = v[1];

    for (i = 2; i < n; i ++) {
        while (pos)
            if (ccp(stk[pos-1], stk[pos],v[i]) >= 0)
                pos--;
            else
                break;
        stk[++pos] = v[i];
    }

    double ans = 0;
    ++ pos;
    for (i = 0; i < pos; i++)
        ans += dist(stk[i], stk[(i + 1) % pos]);
    cout << fixed << setprecision(2) << ans << '\n';
    return 0;
}
