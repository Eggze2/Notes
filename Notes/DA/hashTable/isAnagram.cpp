#include<string>
class Solution {
    public:
    bool isAnagram(std::string s, std::string t) {
        int record[26] = {0};
        for (int i = 0; i < s.size(); i++) {
            record[s[i] - 'a'];
        }
        
    }
};