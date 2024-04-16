#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point
{
    int x; 
    int y;
    int index;
};

int manhattanDistance(const Point &p1, const Point &p2)
{
    return (abs(p1.x - p2.x) + abs(p1.y - p2.y));
}

double angle(const Point &p1, const Point &p2)
{
    return atan2(p2.y - p1.y, p2.x - p1.x);
}

int main()
{
    int N;
    cin >> N;
    vector<Point> points(N);
    cin >> points[0].x >> points[0].y;
    points[0].index = 1;
    Point O = points[0];
    for (int i = 1; i < N; i++)
    {
        cin >> points[i].x >> points[i].y;
        points[i].index = i + 1;
    }
    sort(points.begin() + 1, points.end(), [O](const Point &p1, const Point &p2) {
        double angle1 = angle(O, p1);
        double angle2 = angle(O, p2);
        if (angle1 != angle2)
        {
            return angle1 < angle2;
        }
        return manhattanDistance(O, p1) < manhattanDistance(O, p2);
    });
    cout << N << endl;
    cout << 1 << endl;
    int splitIndex = 0;
    for (int i = 1; i < N - 1; i++)
    {
        Point v1 = {points[i].x - O.x, points[i].y - O.y};
        Point v2 = {points[i + 1].x - O.x, points[i + 1].y - O.y};
        if ((v1.x * v2.y - v2.x * v1.y) < 0 || (v1.x * v2.y - v2.x * v1.y) == 0 && (v1.x * v2.x + v1.y * v2.y) < 0)
        {
            splitIndex = i;
        }
    }
    for (int i = 0; i < N - 1; i++)
    {
        cout << points[(splitIndex + i) % (N - 1) + 1].index << endl;
    }
    return 0;
}
