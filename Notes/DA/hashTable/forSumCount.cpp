#include <vector>
#include <unordered_map>
class Solution {
    public:
    int forSumCount(std::vector<int>& A, std::vector<int> B, std::vector<int>& C, std::vector<int>& D) {
        std::unordered_map<int, int> umap;   // key：a+b的数值，value：a+b出现的次数
        for (int a : A) {
            for (int b : B) {
                umap[a + b]++;
            }
        }
        int count = 0;
        for (int c : C) {
            for (int d : D) {
                if (umap.find(0 - (c + d)) != umap.end()) {
                    count += umap[0 - (c + d)];
                }
            }
        }
        return count;
    }
};