/**
 * 实现 strStr() 函数。
 * 给定一个 haystack 字符串和一个 needle 字符串，
 * 在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。
 * 如果不存在，则返回  -1。
 * 示例 1: 输入: haystack = "hello", needle = "ll" 输出: 2
 * 示例 2: 输入: haystack = "aaaaa", needle = "bba" 输出: -1
 * 当 needle 是空字符串时返回 0
*/
#include <string>
#include <vector>
class Solution {
public:
    // 计算最长前缀后缀数组（Longest Prefix Suffix Array）
    void computeLPSArray(const std::string& needle, std::vector<int>& lps) {
        int length = 0; // needle的最长公共前后缀的长度
        lps[0] = 0; // lps的第一个值总是0
        int i = 1;
        while (i < needle.length()) {
            if (needle[i] == needle[length]) {
                length++;
                lps[i] = length;
                i++;
            }
            else {
                if (length != 0) {
                    length = lps[length - 1];
                }
                else {
                    lps[i] = 0;
                    i++;
                }
            }
        }  
    }

    // 实现KMP算法来找出needle字符串在haystack字符串中的第一个匹配项的下标
    int strStr(const std::string& haystack, const std::string& needle) {
        if (needle.empty()) return 0;   // 如果needle为空字符串，则返回0
        if (haystack.length() < needle.length()) return -1; // 如果haystack比needle短，则返回-1。PS：其实也可以值判断半长

        int M = needle.length();
        int N = haystack.length();

        std::vector<int> lps(M);
        computeLPSArray(needle, lps);   // 计算lps数组

        int i = 0; // index for haystack
        int j = 0; // index for needle
        while (i < N) {
            if (needle[j] == haystack[i]) {
                j++;
                i++;
            }
            if (j == M) {
                return i - j;   // 找到匹配，返回起始索引
            }
            if (i < N && needle[j] != haystack[i]) {
                if (j != 0)
                    j = lps[j - 1];
                else
                    i = i + 1;
            }
        }
        return -1;  // 未找到匹配，返回-1
    }



    // 前缀表统一减一
    void getNext(int* next, const std::string& s) {
        next = new int[s.size()];
        // 1. 初始化：
        // 定义两个指针i和j，j指向前缀末尾位置，i指向后缀末尾位置
        // next[i] 表示i（包括i）之前最长相等的前后缀长度（其实就是j）
        // 所以初始化 next[0] = j
        int j = -1;
        next[0] = j;
        // 2. 处理前后缀不同的情况
        // 因为j初始化为-1，那么i就从1开始，进行 s[i] 与 s[j+1] 的比较。
        // 所以遍历模式串s的循环下标i要从1开始
        for (int i = 1; i < s.size(); i++) {
            // 如果 s[i] 与 s[j+1] 不相同，也就是遇到前后缀末尾不相同的情况，就要向前回退
            // next[j] 就是记录着j（包括j）之前的子串的相同前后缀的长度。
            // 那么 s[i] 与 s[j+1] 不相同，就要找j+1前一个元素在next数组里的值（就是next[j]）
            while (j >= 0 && s[i] != s[j + 1]) {
                j = next[j];
            }
            // 3. 处理前后缀相同的情况
            // 如果 s[i] 与 s[j + 1] 相同，那么就同时向后移动i和j说明找到了相同的前后缀，
            // 同时还要将j（前缀的长度）赋给next[i], 因为next[i]要记录相同前后缀的长度
            if (s[i] == s[j + 1]) {
                j++;
            }
            next[i] = j;
        }
    }
    int strStr(std::string haystack, std::string needle) {
        if (needle.size() == 0) {
            return 0;
        }
        int* next;
        getNext(next, needle);
        int j = -1;
        // 在文本串s里找是否出现过模式串t。
        // 定义两个下标j指向模式串起始位置，i指向文本串起始位置。
        // 那么j初始值依然为-1，依然因为next数组里记录的起始位置为-1
        for (int i = 0; i < haystack.size(); i++) {
            // 接下来就是 s[i] 与 t[j + 1]（因为j从-1开始的）进行比较。
            // 如果 s[i] 与 t[j + 1] 不相同，j就要从next数组里寻找下一个匹配的位置
            while (j >= 0 && haystack[i] != needle[j + 1])
            {
                j = next[j];
            }
            // 如果 s[i] 与 t[j + 1] 相同，那么i和j同时向后移动
            if (haystack[i] == needle[j + 1]) {
                j++;
            }
            // 如果j指向了模式串t的末尾，那么就说明模式串t完全匹配文本串s里的某个子串了。
            // 本题要在文本串字符串中找出模式串出现的第一个位置 (从0开始)，
            // 所以返回当前在文本串匹配模式串的位置i减去模式串的长度，
            // 就是文本串字符串中出现模式串的第一个位置
            if (j == (needle.size() - 1)) {
                return (i - needle.size() + 1);
            }
        }
        delete[] next;
        return -1;
    }
    // 前缀表不减一
    void getNext(int* next, const std::string& s) {
        next = new int[s.size()];

        int j = 0;
        next[0] = j;
        for (int i = 1; i < s.size(); i++) {
            while (j >= 0 && s[i] != s[j + 1]) {
                j = next[j - 1];
            }
            if (s[i] == s[j]) {
                j++;
            }
            next[i] = j;
        }
    }
    int strStr(std::string haystack, std::string needle) {
        if (needle.size() == 0) {
            return 0;
        }
        int* next;
        getNext(next, needle);
        int j = 0;
        for (int i = 0; i < haystack.size(); i++) {
            while (j >= 0 && haystack[i] != needle[j])
            {
                j = next[j - 1];
            }
            if (haystack[i] == needle[j]) {
                j++;
            }
            if (j == (needle.size())) {
                return (i - needle.size());
            }
        }
        delete[] next;
        return -1;
    }
};