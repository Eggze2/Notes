//#include <iostream>
//
//using namespace std;
//
//int judgeQuadrant(int x, int y, int size) {
//    int mid = 1 << (size - 1); 
//    if (x > mid) {
//        return y > mid ? 4 : 1;
//    }
//    else {
//        return y > mid ? 3 : 2;
//    }
//}
//
//void placeL(int** square, int x, int y, int n, int m, int midX, int midY) {
//
//    if (n == 1) {  // if the hole is in the current 2x2 block
//        if (square[midX][midY] == -1 || square[midX - 1][midY] == -1 || square[midX][midY - 1] == -1 || square[midX - 1][midY - 1] == -1) {
//            int size = 1 << n;
//            int quadrant = judgeQuadrant(x, y, size);
//            if (quadrant == 1) {
//                square[midX - 1][midY - 1] = m;
//                square[midX][midY - 1] = m;
//                square[midX][midY] = m;
//            }
//            else if (quadrant == 2) {
//                square[midX - 1][midY] = m;
//                square[midX][midY - 1] = m;
//                square[midX][midY] = m;
//            }
//            else if (quadrant == 3) {
//                square[midX - 1][midY] = m;
//                square[midX - 1][midY - 1] = m;
//                square[midX][midY] = m;
//            }
//            else if (quadrant == 4) {
//                square[midX - 1][midY] = m;
//                square[midX - 1][midY - 1] = m;
//                square[midX][midY - 1] = m;
//            }
//            if (n >= 2 || m > 1) {
//                placeL(square, midX - 1, midY, n--, m--, midX - midX / 2, midY + midY / 2);
//                placeL(square, midX - 1, midY - 1, n--, m--, midX - midX / 2, midY - midY / 2);
//                placeL(square, midX, midY - 1, n--, m--, midX + midX / 2, midY - midY / 2);
//                placeL(square, midX, midY, n--, m--, midX + midX / 2, midY + midY / 2);
//            }            
//        }
//        return;
//    }    
//}
//
//void printSquare(int** square, int size) {
//    for (int i = 0; i < size; ++i) {
//        for (int j = 0; j < size; ++j) {
//            cout << square[i][j] << " ";
//        }
//        cout << endl;
//    }
//}
//
//int main() {
//    int n;
//    cin >> n;
//    int x, y;
//    cin >> x >> y;
//    if (n < 1 || n > 9 || x < 1 || y < 1 || x >(1 << n) || y >(1 << n)) {
//        cout << "Out of bound!" << endl;
//        return 1;
//    }
//    else {
//        int m = ((1 << (2 * n)) - 1) / 3;
//        cout << "m = " << m << endl;
//        int size = 1 << n;
//        int** square = new int* [size];
//        for (int i = 0; i < size; ++i) {
//            square[i] = new int[size];
//            for (int j = 0; j < size; ++j) {
//				square[i][j] = -1;
//			}
//        }
//        square[x - 1][y - 1] = 0;
//        placeL(square, x, y, n, m, size / 2, size /2);
//        printSquare(square, size);
//        for (int i = 0; i < size; ++i) {
//            delete[] square[i];
//        }
//        delete[] square;
//        return 0;     
//    }
//}
//#include <iostream>
//using namespace std;
//
//void printSquare(int** square, int size) {
//    for (int i = 0; i < size; ++i) {
//        for (int j = 0; j < size; ++j) {
//            cout << square[i][j] << " ";
//        }
//        cout << endl;
//    }
//}
//
//void placeL(int** square, int size, int x, int y, int& m, int hx, int hy) {
//    if (size == 2) {
//        for (int dx = 0; dx < 2; dx++) {
//            for (int dy = 0; dy < 2; dy++) {
//                if (x + dx != hx || y + dy != hy) {
//                    square[x + dx][y + dy] = m;
//                }
//            }
//        }
//        m--; // 对每个2x2区域完成后，减少m以确保下一个L型块的值不同
//        return;
//    }
//
//    int halfSize = size / 2;
//    int midX = x + halfSize - 1;
//    int midY = y + halfSize - 1;
//
//    // 分别处理四个象限
//    if (hx < midX + 1 && hy < midY + 1) { // 第一象限
//        placeL(square, halfSize, x, y, m, hx, hy);
//    }
//    else {
//        placeL(square, halfSize, x, y, m, midX, midY); // 放置假洞
//    }
//
//    if (hx < midX + 1 && hy >= y + halfSize) { // 第二象限
//        placeL(square, halfSize, x, y + halfSize, m, hx, hy);
//    }
//    else {
//        placeL(square, halfSize, x, y + halfSize, m, midX, midY + 1); // 放置假洞
//    }
//
//    if (hx >= x + halfSize && hy < midY + 1) { // 第三象限
//        placeL(square, halfSize, x + halfSize, y, m, hx, hy);
//    }
//    else {
//        placeL(square, halfSize, x + halfSize, y, m, midX + 1, midY); // 放置假洞
//    }
//
//    if (hx >= x + halfSize && hy >= y + halfSize) { // 第四象限
//        placeL(square, halfSize, x + halfSize, y + halfSize, m, hx, hy);
//    }
//    else {
//        placeL(square, halfSize, x + halfSize, y + halfSize, m, midX + 1, midY + 1); // 放置假洞
//    }
//
//    // 在四个象限中心填充L型块
//    if (square[midX][midY] == 0) square[midX][midY] = m;
//    if (square[midX + 1][midY] == 0) square[midX + 1][midY] = m;
//    if (square[midX][midY + 1] == 0) square[midX][midY + 1] = m;
//    if (square[midX + 1][midY + 1] == 0) square[midX + 1][midY + 1] = m;
//    m--; // 减少m以确保下一个L型块的值不同
//}
//
//
//int main() {
//    int n; // 矩阵大小的指数
//    cout << "Enter the power of 2 for the size of the square matrix: ";
//    cin >> n;
//    int size = 1 << n; // 实际的矩阵大小
//
//    // 输入"洞"的位置
//    int hx, hy;
//    cout << "Enter the coordinates (x,y) for the hole (1-based index): ";
//    cin >> hx >> hy;
//    hx--; // 转换为0-based index
//    hy--; // 转换为0-based index
//
//    // 初始化矩阵
//    int** square = new int* [size];
//    for (int i = 0; i < size; ++i) {
//        square[i] = new int[size];
//        fill(square[i], square[i] + size, 0); // 填充-1代表未填充状态
//    }
//    int m = ((1 << (2 * n)) - 1) / 3;
//    // 调用填充函数
//    placeL(square, size, 0, 0, m, hx, hy);
//
//    // 打印结果矩阵
//    printSquare(square, size);
//
//    // 清理动态分配的内存
//    for (int i = 0; i < size; ++i) {
//        delete[] square[i];
//    }
//    delete[] square;
//
//    return 0;
//}

#include <iostream>
#include <vector>

using namespace std;

void printSquare(const vector<vector<int>>& square) {
    for (const auto& row : square) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

void placeL(vector<vector<int>>& square, int size, int x, int y, int& m, int hx, int hy) {
    if (size == 2) {
        for (int dx = 0; dx < 2; dx++) {
            for (int dy = 0; dy < 2; dy++) {
                if (x + dx != hx || y + dy != hy) {
                    square[x + dx][y + dy] = m;
                }
            }
        }
        m--;
        return;
    }

    int halfSize = size / 2, midX = x + halfSize - 1, midY = y + halfSize - 1;

    // 递归分四个象限
    int offsets[4][2] = { {0, 0}, {0, halfSize}, {halfSize, 0}, {halfSize, halfSize} };
    int fakeHoles[4][2] = { {midX, midY}, {midX, midY + 1}, {midX + 1, midY}, {midX + 1, midY + 1} };

    for (int i = 0; i < 4; i++) {
        int newX = x + offsets[i][0], newY = y + offsets[i][1];
        int newHX = hx, newHY = hy;

        if (!(newHX >= newX && newHX < newX + halfSize && newHY >= newY && newHY < newY + halfSize)) {
            newHX = fakeHoles[i][0];
            newHY = fakeHoles[i][1];
        }

        placeL(square, halfSize, newX, newY, m, newHX, newHY);
    }

    if (square[midX][midY] == 0) square[midX][midY] = m;
    if (square[midX + 1][midY] == 0) square[midX + 1][midY] = m;
    if (square[midX][midY + 1] == 0) square[midX][midY + 1] = m;
    if (square[midX + 1][midY + 1] == 0) square[midX + 1][midY + 1] = m;
    m--;
}

int main() {
    int n;
    //cout << "Enter the power of 2 for the size of the square matrix: ";
    cin >> n;
    int size = 1 << n, hx, hy;
    //cout << "Enter the coordinates (x,y) for the hole (1-based index): ";
    cin >> hx >> hy;
    hx--; hy--; // Adjust for 0-based indexing

    vector<vector<int>> square(size, vector<int>(size, 0));
    int m = ((1 << (2 * n)) - 1) / 3;

    placeL(square, size, 0, 0, m, hx, hy);
    square[hx][hy] = 0;
    printSquare(square);

    return 0;
}
