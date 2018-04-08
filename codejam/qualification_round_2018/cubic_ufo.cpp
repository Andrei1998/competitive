#include <bits/stdc++.h>

using namespace std;

template <class T> struct Point3D {
	typedef Point3D P;
	typedef const P& R;
	T x, y, z;
	explicit Point3D(T x=0, T y=0, T z=0) : x(x), y(y), z(z) {}
	bool operator<(R p) const {
		return tie(y, x, z) < tie(p.y, p.x, p.z); }
	bool operator==(R p) const {
		return tie(x, y, z) == tie(p.x, p.y, p.z); }
	P operator+(R p) const { return P(x+p.x, y+p.y, z+p.z); }
	P operator-(R p) const { return P(x-p.x, y-p.y, z-p.z); }
	P operator*(T d) const { return P(x*d, y*d, z*d); }
	P operator/(T d) const { return P(x/d, y/d, z/d); }
	T dot(R p) const { return x*p.x + y*p.y + z*p.z; }
	P cross(R p) const {
		return P(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
	}
	
	T dist2() const { return x*x + y*y + z*z; }
	double dist() const { return sqrt((double)dist2()); }
	P unit() const { return *this/(T)dist(); } //makes dist()=1
	
	P rotate(double angle, P axis) const {
		double s = sin(angle), c = cos(angle); P u = axis.unit();
		return u*dot(u)*(1-c) + (*this)*c - cross(u)*s;
	}
    friend ostream& operator<<(ostream& f, P p) {
        return f << p.x << ' ' << p.y << ' ' << p.z;
    }
};

typedef Point3D <double> P;

const P P1(0.5, 0.5, 0.5);
const P P2(0.5, 0.5, -0.5);
const P P3(0.5, -0.5, 0.5);
const P P4(0.5, -0.5, -0.5);
const P P5(-0.5, 0.5, 0.5);
const P P6(-0.5, 0.5, -0.5);
const P P7(-0.5, -0.5, 0.5);
const P P8(-0.5, -0.5, -0.5);

const vector <P> cube = {P1, P2, P3, P4, P5, P6, P7, P8};

double project(const vector <P> &cube) {
    const P p1 = *max_element(cube.begin(), cube.end());
    const P p2 = *min_element(cube.begin(), cube.end());
    return (p1 - p2).y;
}

const double PI = acos(-1);

vector <P> getRotCube(const double angleOX, const double angleOZ) {
    auto c = cube;
    for (auto &it: c) {
        it = it.rotate(angleOX * PI / 180, P(1, 0, 0));  
        it = it.rotate(angleOZ * PI / 180, P(0, 0, 1));  
    }
    return c;
}

vector <P> getRotCube(const double angle) {
    if (angle <= 45)
        return getRotCube(angle, 0);
    else
        return getRotCube(45, angle - 45);
}

void printCube(const vector <P> &cube) {
    const P &P1 = cube[0], &P2 = cube[1], &P3 = cube[2], &P4 = cube[3]; 
    const P &P5 = cube[4], &P6 = cube[5], &P7 = cube[6], &P8 = cube[7]; 

    cout << (P1 + P2 + P3 + P4) / 4 << '\n';
    cout << (P3 + P4 + P7 + P8) / 4 << '\n';
    cout << (P2 + P4 + P6 + P8) / 4 << '\n';        
}

void test() {
    double A;
    cin >> A;

    double l = 0, r = 90;
    for (int i = 0; i < 200; ++ i) {
        const double mid = (l + r) / 2;
        const auto cb = getRotCube(mid);
        if (project(cb) < A)
            l = mid;
        else
            r = mid;
    }

    const auto cb = getRotCube(l);
    printCube(cb);
}

int main() {
    int T = 0;
    cin >> T;
    for (int i = 1; i <= T; ++ i) {
        cout << "Case #" << i << ":\n";
        cout << fixed << setprecision(12);
        test();
    }  
    return 0;
}
