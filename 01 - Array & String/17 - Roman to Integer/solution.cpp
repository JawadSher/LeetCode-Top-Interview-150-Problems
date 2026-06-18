class Solution {
public:
    int romanToInt(string s) {
       unordered_map<char, int> roman = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
        };

        int num = 0;
        int n = s.length();
        for(int i = 0; i < n; i++){
            if(i+1 < n && roman[s[i]] < roman[s[i+1]]){
                num += roman[s[i+1]] - roman[s[i]];
                i++;
            }else num += roman[s[i]];
        }

        return num;
    }
};
