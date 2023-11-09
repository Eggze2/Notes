#include <string>
#include <algorithm>
class Solution {
public:
    std::string reverseStr(std::string s, int k) {
        for (int i = 0; i < s.size(); i += (2 * k)) {
            // 每隔 2k 个字符的前 k 个字符进行反转
            // 剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符
            if (i + k <= s.size()) {
                std::reverse(s.begin() + i, s.begin() + i + k);
            } else {
                // 剩余字符少于 k 个， 则将剩余字符全部反转
                std::reverse(s.begin() + i, s.end());
            }
        }
        return s;
    }
    // use own "reverse" function
    void reverse(std::string& s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            std::swap(s[i], s[j]);
        }
    }
    std::string reverseStr(std::string s, int k) {
        for (int i = 0; i < s.size(); i += (2 * k)) {
            if (i + k <= s.size()) {
                reverse(s, i, i + k - 1);
                continue;
            }
            reverse(s, i, s.size() - 1);
        }
        return s;
    }

    std::string reverseStr(std::string s, int k) {
        int n = s.size(), pos = 0;
        while (pos < n) {
            // 剩余字符串大于或等于 k 的情况
            if (pos + k < n) std::reverse(s.begin() + pos, s.begin() + pos + k);
            else std::reverse(s.begin() + pos, s.end());
            pos += 2 * k;
        }
        return s;
    }
};