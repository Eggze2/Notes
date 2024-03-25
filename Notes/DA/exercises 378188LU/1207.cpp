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

#include <iostream>
#include <vector>
using namespace std;

struct Point {
    long long x, y;
    int id;
};

vector<Point> points;

// 比较函数，用于根据极角排序
bool compareByPolarAngle(const Point& p1, const Point& p2) {
    return ((p1.x - points[0].x) * (p2.y - points[0].y) - (p2.x - points[0].x) * (p1.y - points[0].y)) > 0;
}

// 手动实现排序函数（类似于插入排序）
void sortPointsByPolarAngle(vector<Point>& points, int start, int end) {
    for (int i = start + 1; i < end; i++) {
        Point key = points[i];
        int j = i - 1;
        while (j >= start && compareByPolarAngle(key, points[j])) {
            points[j + 1] = points[j];
            j--;
        }
        points[j + 1] = key;
    }
}

int main() {
    int N;
    cin >> N;
    points.resize(N);

    // 读取点并找到最左下的点
    Point leftLowest = { LLONG_MAX, LLONG_MAX, -1 };
    for (int i = 0; i < N; i++) {
        cin >> points[i].x >> points[i].y;
        points[i].id = i + 1;
        if (points[i].x < leftLowest.x || (points[i].x == leftLowest.x && points[i].y < leftLowest.y)) {
            leftLowest = points[i];
        }
    }

    // 将最左下的点交换到第一个位置
    for (int i = 0; i < N; i++) {
        if (points[i].id == leftLowest.id) {
            swap(points[0], points[i]);
            break;
        }
    }

    // 根据极角对点进行排序
    sortPointsByPolarAngle(points, 1, N);

    // 输出结果
    cout << leftLowest.id << " " << points[N / 2].id << endl;
    return 0;
}
