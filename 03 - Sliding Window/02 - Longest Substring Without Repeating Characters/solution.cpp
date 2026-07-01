// O(n)2 - Unoptimized Solution
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.length() == 0) return 0;
        if(s.length() == 1) return 1;

        string subStr = "";
        int len = 0;
        for(int i = 0; i < s.length(); i++){
            int j = 0;

            while(j < subStr.length()){
                if(subStr[j] == s[i]) {
                    subStr = subStr.substr(j + 1);
                    break;
                }

                j++;
            }

            subStr += s[i];

            len = max<int>(len, subStr.length());
        }


        return len;
    }
};
