#include<string>
class Solution {
    public:
    bool isAnagram(std::string s, std::string t) {
        int record[26] = {0};
        for (int i = 0; i < s.size(); i++) {
            record[s[i] - 'a'];
        }
        
        for (int i = 0; i < t.length(); i++) {
            record[t[i] - 'a']--;
        }

        for (int i = 0; i < 26; i++) {
            if (record[i] != 0) {
                // record数组如果有的元素不为零0，说明字符串s和t中的某个多了或少了字符
                return false;
            }
        }
        return true;
    }
};