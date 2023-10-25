#include <string>
class Solution {
public:
    bool canConstruct(std::string ransomNote, std::string magazine) {
        // 暴解
        for (int i = 0; i < magazine.length(); i++) {
            for (int j = 0; j < ransomNote.length(); j++) {
                if (magazine[i] == ransomNote[j]) {
                    ransomNote.erase(ransomNote.begin() + j);
                    break;
                }
            }
        }
        if (ransomNote.length() == 0) {
            return true;
        }
        return false;
    }
    // Hash
    bool canConstruct(std::string ransomNote, std::string magazine) {
        int record[26] = {0};
        if (ransomNote.size() > magazine.size()) {
            return false;
        }
        for (int i = 0; i < magazine.length(); i++) {
            record[magazine[i] - 'a']++;
        }
        for (int j = 0; j < ransomNote.length(); j++) {
            record[ransomNote[j] - 'a']--;
            if (record[ransomNote[j] - 'a'] < 0) {
                return false;
            }
        }
        return true;
    }
};