#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <utility>

using namespace std;

struct Point {
    int x, y;
    friend bool operator==(const Point &A, const Point &B) {
        return A.x == B.x && A.y == B.y;
    }
    friend bool operator!=(const Point &A, const Point &B) {
        return A.x != B.x || A.y != B.y;
    }
    friend bool operator<(const Point &A, const Point &B) {
        if (A.x != B.x)
            return A.x < B.x;
        else
            return A.y < B.y;
    }
    Point(int _x = 0, int _y = 0):
        x(_x), y(_y) {}
};

double Dist(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

set <Point> points;

bool onSegment(Point p, Point q, Point r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
       return true;
    return false;
}

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
    if (val == 0)
        return 0;
    return (val > 0) ? 1 : 2;
}

int ccw(Point p, Point q, Point r) {
    int val = (p.x - q.x) * (r.y - q.y) - (p.y - q.y) * (r.x - q.x);
    return val;
}

bool sameSide(Point a, Point b, Point p, Point q) {
    return 1LL * ccw(a, b, p) * ccw(a, b, q) > 0;
}

bool inside(Point a, Point b, Point c, Point p) {
    return sameSide(a, b, c, p) && sameSide(b, c, a, p) && sameSide(c, a, b, p);
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;
    if (o1 == 0 && onSegment(p1, p2, q1))
        return true;
    if (o2 == 0 && onSegment(p1, q2, q1))
        return true;
    if (o3 == 0 && onSegment(p2, p1, q2))
        return true;
    if (o4 == 0 && onSegment(p2, q1, q2))
        return true;
    return false;
}

bool realIntersect(Point p1, Point q1, Point p2, Point q2) {
    return 1LL * ccw(p1, q1, p2) * ccw(p1, q1, q2) < 0 && 1LL * ccw(p2, q2, p1) * ccw(p2, q2, q1) < 0;
}

vector <pair <Point, Point> > edges;

map <Point, Point> father;
map <Point, int> h;

Point find(const Point &p) {
    if (!father.count(p))
        return p;
    else {
        father[p] = find(father[p]);
        return father[p];
    }
}

bool unite(Point a, Point b) {
    a = find(a), b = find(b);
    if (a == b)
        return false;

    if (h[a] < h[b])
        father[a] = b;
    else {
        if (h[a] == h[b])
            ++ h[a];
        father[b] = a;
    }
    return true;
}

struct Edge {
    Point p1, p2;
    double dist;

    friend bool operator<(const Edge &a, const Edge &b) {
        return a.dist < b.dist;
    }

    Edge(Point _p1, Point _p2): p1(_p1), p2(_p2) {
        dist = Dist(p1, p2);
    }
};

vector <Edge> goodEdges;

const double PI = acos(-1);

Point _center;

struct Segment {
    Point p1, p2;

    Segment(Point _p1 = 0, Point _p2 = 0):
        p1(_p1), p2(_p2) {}

    friend bool operator<(const Segment &a, const Segment &b) {
        return realIntersect(_center, b.p1, a.p1, a.p2) || realIntersect(_center, b.p2, a.p1, a.p2) || inside(_center, b.p1, b.p2, a.p1) || inside(_center, b.p1, b.p2, a.p2);
    }
};

struct Event {
    double angle;
    int type;
    Point p;
    Segment s;

    Event(double _angle = 0, int _type = 0, Point _p = 0, Segment _s = Segment(0, 0)):
        angle(_angle), type(_type), p(_p), s(_s) {}

    friend bool operator<(const Event &a, const Event &b) {
        if (a.angle != b.angle)
            return a.angle < b.angle;
        else
            return a.type < b.type;
    }
};

set <Segment> Set;

void sweep(const Point &center) {
    Set.clear();
    _center = center;
    vector <Event> events;
    for (auto p: points) //Query events
        if (p != center)
            events.push_back(Event(atan2(p.y - center.y, p.x - center.x), 0, p));

    for (auto edg: edges)
        if (edg.first != center && edg.second != center) { //Update events
            Point p1 = edg.first;
            Point p2 = edg.second;

            double ang1 = atan2(p1.y - center.y, p1.x - center.x);
            double ang2 = atan2(p2.y - center.y, p2.x - center.x);

            if (ang1 > ang2)
                swap(ang1, ang2);

            if (ang2 - ang1 >= PI) { //Has origin
                Set.insert(Segment(p1, p2));
                events.push_back(Event(ang1, -1, 0, Segment(p1, p2)));
                events.push_back(Event(ang2, 1, 0, Segment(p1, p2)));
            }
            else {
                events.push_back(Event(ang1, 1, 0, Segment(p1, p2)));
                events.push_back(Event(ang2, -1, 0, Segment(p1, p2)));
            }
        }

    sort(events.begin(), events.end());
    for (auto ev: events) {
        if (ev.type == 0) {
            if (Set.empty())
                goodEdges.push_back(Edge(center, ev.p));
            else {
                Point p1 = Set.begin() -> p1;
                Point p2 = Set.begin() -> p2;
                if (!(p1 != center && p1 != ev.p && p2 != center && p2 != ev.p && doIntersect(center, ev.p, p1, p2)))
                    goodEdges.push_back(Edge(center, ev.p));
            }
        }
        else if (ev.type == -1)
            Set.erase(Set.find(ev.s));
        else
            Set.insert(ev.s);
    }
}

void buildGoodEdges() {
    for (auto p: points)
        sweep(p);
}

int main() {
    //freopen("data.in", "r", stdin);
    int N;
    cin >> N;

    for (int i = 1; i <= N; ++ i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        edges.push_back(make_pair(Point(x1, y1), Point(x2, y2)));
        points.insert(Point(x1, y1));
        points.insert(Point(x2, y2));
        unite(Point(x1, y1), Point(x2, y2));
    }

    buildGoodEdges();

    double ans = 0;
    sort(goodEdges.begin(), goodEdges.end());

    for (auto edg: goodEdges)
        if (unite(edg.p1, edg.p2))
            ans += edg.dist;
    cout << fixed << setprecision(10) << ans << '\n';
    return 0;
}
