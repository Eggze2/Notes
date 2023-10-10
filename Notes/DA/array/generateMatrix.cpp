#include <vector>
class Solution {
public:
    std::vector<std::vector<int>> generateMatrix(int n) {
        std::vector<std::vector<int>> res(n, std::vector<int>(n, 0));
        int startx = 0, starty = 0;
        int loop = n / 2;
        int mid = n / 2;
        int count = 1;  // 用于给矩阵中的空格赋值
        int offset = 1;     // 控制每一条边遍历的长度，每循环一次右边界收缩一位
        int i, j;
        while (loop--) {
            i = startx;
            j = starty;

            for (j = starty; j < n - offset; j++) {
                res[startx][j] = count++;
            }
            for (i = startx; i < n - offset; i++) {
                res[i][j] = count++;
            }
            for (; j > starty; j--) {
                res[i][j] = count++;
            }
            for (; i > startx; i--) {
                res[i][j] = count++;
            }

            startx++;
            starty++;

            offset++;
        }
        if (n % 2) {
            res[mid][mid] = count;
        }
        return res;
    }
};