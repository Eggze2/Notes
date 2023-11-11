#include <string>
class Solution {
public:
// 前缀表统一减一
    void getNext(int* next, const std::string& s) {
        next = new int[s.size()];
        int j = -1;
        next[0] = -1;
        for (int i = 0; i < s.size(); i++) {
            while (j >= 0 && s[i] != s[j + 1]) {
                j = next[j];
            }
            if (s[i] == s[j + 1]) {
                j++;
            }
            next[i] = j;
        }
    }
    bool repeatedSubstringPattern(std::string s) {
        if (s.size() == 0) {
            return false;
        }
        int* next;
        getNext(next, s);
        int len = s.size();
        if (next[len - 1] != -1 && len % (len - (next[len - 1] + 1)) == 0) {
            return true;
        }
        return false;
    }
    // 前缀表不减一
    void getNext (int* next, const std::string& s){
        next = new int[s.size()];
        int j = 0;
        next[0] = 0;
        for(int i = 1;i < s.size(); i++){
            while(j > 0 && s[i] != s[j]) {
                j = next[j - 1];
            }
            if(s[i] == s[j]) {
                j++;
            }
            next[i] = j;
        }
    }
    bool repeatedSubstringPattern (std::string s) {
        if (s.size() == 0) {
            return false;
        }
        int* next;
        getNext(next, s);
        int len = s.size();
        if (next[len - 1] != 0 && len % (len - (next[len - 1] )) == 0) {
            return true;
        }
        return false;
    }
};