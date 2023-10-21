#include <vector> 
#include <unordered_map>
class Solutio {
    public: 
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map <int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            auto iter = map.find(target - nums[i]);
            if (iter != map.end()) {
                return {iter->second, i};
            }
            map.insert(std::pair<int, int>(nums[i], i));
        }
        return {};
    }
};