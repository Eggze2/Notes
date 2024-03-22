// #include <iostream>
// #include <vector>
// #include <cmath>
// using namespace std;

// typedef long long LL;
// #define Rep(i, a, b) for(int i = a; i < b; i++)
// #define rep(i, n) for(int i = 0; i < n; i++)

// struct Point {
//     LL x, y;
//     Point(LL xCoord = 0, LL yCoord = 0) : x(xCoord), y(yCoord) {}
// };

// struct Line {
//     LL A, B, C;
//     Line(const Point& p1, const Point& p2) {
//         A = p2.y - p1.y;
//         B = p1.x - p2.x;
//         C = -A * p1.x - B * p1.y;
//     }
// };

// void dividePoints(const vector<Point>& points) {
//     int n = points.size();
//     rep(i, n - 1) {
//         Rep(j, i + 1, n) {
//             Line line(points[i], points[j]);
//             int x = 0;
//             rep(k, n) {
//                 if (k != i && k != j) {
//                     LL distance = line.A * points[k].x + line.B * points[k].y + line.C;
//                     if (distance > 0)
//                         x++;
//                     else if (distance < 0)
//                         x--;
//                 }
//             }
//             if (x == 0) {
//                 printf("%d %d", i+1,j+1);
//                 return;
//             }
//         }
//     }
// }

// int main() {
//     int N;
//     cin >> N;
//     vector<Point> points(N);
//     rep(i, N) {
//         cin >> points[i].x >> points[i].y;
//     }
//     dividePoints(points);

//     return 0;
// }

// #include <iostream>
// #include <vector>
// #include <unordered_map>
// using namespace std;

// typedef long long LL;

// struct Point {
//     LL x, y;
//     Point(LL xCoord = 0, LL yCoord = 0) : x(xCoord), y(yCoord) {}
// };

// // Function to calculate the slope between two points
// double calculateSlope(const Point& p1, const Point& p2) {
//     return (p2.y - p1.y) * 1.0 / (p2.x - p1.x);
// }

// // Function to check if two points form a line with an equal number of points on each side
// bool formEqualLine(const Point& p1, const Point& p2, const vector<Point>& points) {
//     unordered_map<double, int> slopeCount;
//     for (const Point& p : points) {
//         if (!(p.x == p1.x && p.y == p1.y) && !(p.x == p2.x && p.y == p2.y)) {
//             double slope = calculateSlope(p1, p2);
//             double pointSlope = calculateSlope(p1, p);
//             if (slope == pointSlope)
//                 slopeCount[slope]++;
//         }
//     }
//     return slopeCount.size() * 2 == points.size() - 2;
// }

// // Function to find the points forming the desired line
// pair<int, int> dividePoints(const vector<Point>& points) {
//     int n = points.size();
//     for (int i = 0; i < n - 1; ++i) {
//         for (int j = i + 1; j < n; ++j) {
//             if (formEqualLine(points[i], points[j], points))
//                 return {i + 1, j + 1};
//         }
//     }
//     return {-1, -1}; // If no such line found
// }

// int main() {
//     int N;
//     cin >> N;
//     vector<Point> points(N);
//     for (int i = 0; i < N; ++i) {
//         cin >> points[i].x >> points[i].y;
//     }
//     pair<int, int> linePoints = dividePoints(points);
//     cout << linePoints.first << " " << linePoints.second << endl;
//     return 0;
// }

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <deque>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <ctime>
using namespace std;
typedef long long LL;
typedef double DB;
#define For(i, s, t) for(int i = (s); i <= (t); i++)
#define Ford(i, s, t) for(int i = (s); i >= (t); i--)
#define Rep(i, t) for(int i = (0); i < (t); i++)
#define Repd(i, t) for(int i = ((t)-1); i >= (0); i--)
#define rep(i, s, t) for(int i = (s); i < (t); i++)


struct Point {
    LL x, y;
    int id;
};
vector<Point> points;
//theta p1 < p2 ?
bool cross(Point p1, Point p2){
    return ((p1.x-points[0].x)*(p2.y-points[0].y)-(p2.x-points[0].x)*(p1.y-points[0].y)) >= 0;
}


int main() {
    LL X_MAX=1000001;LL Y_MAX=1000001;

    int N, leftlowID;
    scanf("%d", &N);
    points.resize(N);
    Rep(i, N) {
        cin >> points[i].x >> points[i].y;
        points[i].id = i+1;
        if(points[i].x < X_MAX || (points[i].x == X_MAX && points[i].y < Y_MAX))
        {
            leftlowID=points[i].id;
            X_MAX=points[i].x;
            Y_MAX=points[i].y;
        }
        
    }

    swap(points[leftlowID-1], points[0]);

    sort(points.begin()+1, points.end(), cross);


    printf("%d %d",leftlowID, points[N/2].id);

    return 0;
}