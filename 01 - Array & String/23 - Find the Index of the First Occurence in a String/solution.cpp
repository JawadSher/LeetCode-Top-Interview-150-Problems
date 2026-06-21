class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.length();
        int j = needle.length();
        int i = 0;

        while (i <= n-j) {
            if(needle == haystack.substr(i, j)) return i;

            i++;
        }

        return -1;
    }
};
