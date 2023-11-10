#include <string>
#include <algorithm>
class Solution {
public:
    std::string rightReverse(std::string& s, int k) {
        int len = s.size();
        reverse(s.begin(), s.end());
        reverse(s.begin(), s.begin() + k);
        reverse(s.begin() + k, s.end());
        return s;
    }
    std::string rightReverse(std::string& s, int k) {
        int len = s.size();
        reverse(s.begin(), s.begin() + len - k); // 先反转前一段，长度len-n ，注意这里是和版本一的区别
        reverse(s.begin() + len - k, s.end()); // 再反转后一段
        reverse(s.begin(), s.end()); // 整体反转
        return s;
    }
};