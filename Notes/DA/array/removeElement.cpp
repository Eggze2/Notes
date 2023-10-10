#include <vector>
class Solution {
public:
    int removeElement1(std::vector<int>& nums, int val) {
        // 快慢指针法
        int slowIndex = 0;
        for (int fastIndex = 0; fastIndex < nums.size(); fastIndex++) {
            if (val != nums[fastIndex]) {
                nums[slowIndex++] = nums[fastIndex];
            }
        }
        return slowIndex;
    }
    int removeElement2(std::vector<int>& nums, int val) {
        // 相向双指针法
        int leftIndex = 0;
        int rightIndex = nums.size() - 1;
        while (leftIndex <= rightIndex) {
            while (leftIndex <= rightIndex && nums[leftIndex] != val) {
                ++leftIndex;
            }
            while (leftIndex <= rightIndex && nums[rightIndex] == val) {
                --rightIndex;
            }
            if (leftIndex < rightIndex) {
                nums[leftIndex++] = nums[rightIndex--]; 
            }
        }
        return leftIndex;   // leftIndex一定指向了最终数组末尾的下一个元素
    }
};