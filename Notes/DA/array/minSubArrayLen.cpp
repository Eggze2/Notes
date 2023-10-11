#include<vector>
class Solution {
    public:
    int minSubArrayLen1(int s, std::vector<int>& nums) {
        // 暴力解法 
        int result = __INT32_MAX__;
        int sum = 0;    // 子序列的数值之和
        int subLength = 0;  // 子序列的长度
        for (int i = 0; i < nums.size(); i++) {
            sum = 0;
            for (int j = i; j < nums.size(); j++) {
                sum += nums[j];
                if (sum >= s) {
                    subLength = j - i + 1;
                    result = result < subLength ? result : subLength;
                    break;
                }
            }
        }
        return result == __INT32_MAX__ ? 0 : result;
    }
    int minSubArrayLen2(int s, std::vector<int>& nums) {
        // 滑动窗口
        int result = __INT32_MAX__;
        int sum = 0; // 滑动窗口数值之和
        int i = 0; // 滑动窗口起始位置
        int subLength = 0; // 滑动窗口的长度
        for (int j = 0; j < nums.size(); j++) {
            sum += nums[j];
            // 注意这里使用while，每次更新 i（起始位置），并不断比较子序列是否符合条件
            while (sum >= s) {
                subLength = (j - i + 1); // 取子序列的长度
                result = result < subLength ? result : subLength;
                sum -= nums[i++]; // 这里体现出滑动窗口的精髓之处，不断变更i（子序列的起始位置）
            }
        }
        // 如果result没有被赋值的话，就返回0，说明没有符合条件的子序列
        return result == __INT32_MAX__ ? 0 : result;
    } 
};