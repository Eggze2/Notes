#include <vector>
#include <unordered_set>
class Solution {
    public:
    std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::unordered_set<int> result_set;
        std::unordered_set<int> nums_set(nums1.begin(), nums1.end());
        for (int num : nums2) {
            if (nums_set.find(num) != nums_set.end()) {
                /*
                nums_set.find(num) 返回一个迭代器，
                这个迭代器指向 num 在 nums_set 中的位置。
                如果 num 存在于 nums_set 中，迭代器将指向 num，
                否则，迭代器将指向 nums_set.end()，表示未找到。
                nums_set.end()：end() 函数返回一个迭代器，
                指向无序集合的末尾位置。
                如果 find 函数没有找到元素，它会返回 nums_set.end()。
                if (nums_set.find(num) != nums_set.end())：
                这个条件语句检查 num 是否存在于 nums_set 中。
                如果 num 存在，nums_set.find(num) 将返回指向 num 的迭代器，
                所以条件成立，执行下面的代码块
                */
                result_set.insert(num);
            }
        }
        return std::vector<int>(result_set.begin(), result_set.end());
    }
    // 数组的写法
    std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::unordered_set<int> result_set; // 存放结果，之所以用set是为了给结果集去重
        int hash[1005] = {0}; // 默认数值为0
        for (int num : nums1) { // nums1中出现的字母在hash数组中做记录
            hash[num] = 1;
        }
        for (int num : nums2) { // nums2中出现话，result记录
            if (hash[num] == 1) {
                result_set.insert(num);
            }
        }
        return std::vector<int>(result_set.begin(), result_set.end());
    }
};